/** Emulate `cmd1 | cmd2 | more` pipeline using recursion.

http://stackoverflow.com/questions/20434124/recursive-piping-in-unix-environment
*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#define Close(FD) do {                                  \
    int Close_fd = (FD);                                \
    if (close(Close_fd) == -1) {                        \
      perror("close");                                  \
      fprintf(stderr, "%s:%d: close(" #FD ") %d\n",     \
              __FILE__, __LINE__, Close_fd);            \
    }                                                   \
  }while(0)


static int child = 0; /* whether it is a child process relative to main() */

static void report_error_and_exit(const char* msg) {
  perror(msg);
  (child ? _exit : exit)(EXIT_FAILURE);
}

/** move oldfd to newfd */
static void redirect(int oldfd, int newfd) {
  if (oldfd != newfd) {
    if (dup2(oldfd, newfd) != -1)
      Close(oldfd); /* successfully redirected */
    else
      report_error_and_exit("dup2");
  }
}

/** execute `cmds[pos]` command and call itself for the rest of the commands.

    `cmds[]` is NULL-terminate array
    `exec_pipeline()` never returns.
*/
static void exec_pipeline(char* const* cmds[], size_t pos, int in_fd) {
  if (cmds[pos + 1] == NULL) { /* last command */
    redirect(in_fd, STDIN_FILENO); /* read from in_fd, write to STDOUT */
    execvp(cmds[pos][0], cmds[pos]);
    report_error_and_exit("execvp last");
  }
  else { /* $ <in_fd cmds[pos] >fd[1] | <fd[0] cmds[pos+1] ... */
    int fd[2]; /* output pipe */
    if (pipe(fd) == -1)
      report_error_and_exit("pipe");
    switch(fork()) {
    case -1:
      report_error_and_exit("fork");
    case 0: /* child: execute current command `cmds[pos]` */
      child = 1;
      Close(fd[0]); /* unused */
      redirect(in_fd, STDIN_FILENO);  /* read from in_fd */
      redirect(fd[1], STDOUT_FILENO); /* write to fd[1] */
      execvp(cmds[pos][0], cmds[pos]);
      report_error_and_exit("execvp");
    default: /* parent: execute the rest of the commands */
      Close(fd[1]); /* unused */
      Close(in_fd); /* unused */
      exec_pipeline(cmds, pos + 1, fd[0]); /* execute the rest */
    }
  }
}

int main(int argc, char* argv[]) {
  /* `cat file | grep the | more` */
  const char* cmd1[] = { "cat" , argv[argc-1], NULL };
  const char* cmd2[] = { "grep", "the", NULL };
  const char* more[] = { "more", NULL };
  const char* const* cmds[] = { cmd1, cmd2, more, NULL };

  if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) /* POSIX.1-2001 reap children */
    report_error_and_exit("signal");

  exec_pipeline((char* const**)cmds, 0, STDIN_FILENO);
}
