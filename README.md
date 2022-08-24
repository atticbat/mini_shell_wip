# mini_shell_wip TASKS
work in progress
Follow and check the drive all the time ;)
https://docs.google.com/spreadsheets/d/1fTTD3yJaak-v9SkuEB6YtVW7lW03BgFc12UJoI9eVo0/edit?usp=sharing
to pull and merge
$ git pull origin other-branch  (or try)    $ git fetch origin other-branch && git merge other-branch

However, this would not be a fast-forward merge:

v master
O-O-O
\
 \-O-O-O-O
         ^ other-branch
To solve your problem, first fetch the remote branch:

$ git fetch origin other-branch
Then merge it into your current branch (I'll assume that's master), and fix any merge conflicts:

$ git merge origin/other-branch
# Fix merge conflicts, if they occur
# Add merge conflict fixes
$ git commit    # And commit the merge!


KEEP IN MIND THIS PAGE TO CHECK THE VARIABLE [[https://stackoverflow.com/questions/2821043/allowed-characters-in-linux-environment-variable-names]]|LINK
 - In summary the ones which are allowed as VAR names are a-z, A-Z, 1-9, '_'.
 - Never starting with a number.
Convention made by the ISO in Minishell
