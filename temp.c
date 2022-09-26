/* redirection intput and output with pipe() */
static void	redir(char *cmd)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		die("pipe");
	pid = fork();
	if (pid < 0)
		die("fork");
	if (pid > 0)
	{
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		exec_cmd(cmd);
	}
}

/* main */
int	main(int argc, char *argv[])
{
	int	i;
	int	fd_io[2];

	if ((argc >= 5 && ft_strncmp(argv[1], "here_doc", 9)) || argc >= 6)
	{
		if (!ft_strncmp(argv[1], "here_doc", 9))
		{
			handle_here_doc(argv[2]);
			fd_io[F_OP] = open_f(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND);
			i = 2;
		}
		else
		{
			fd_io[F_IP] = open_f(argv[1], O_RDONLY);
			fd_io[F_OP] = open_f(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC);
			dup2(fd_io[F_IP], STDIN_FILENO);
			i = 1;
		}
		while (++i < argc - 2)
			redir(argv[i]);
		dup2(fd_io[F_OP], STDOUT_FILENO);
		exec_cmd(argv[i]);
	}
	ft_putstr_fd("Error: invalid arguments\n", STDERR_FILENO);
	return (EXIT_FAILURE);