#include "../minishell.h"

int	pipe_loop(t_cmd *cmds, t_shell *shell)
{
	int	fd[2];
	int	pid;
	char	buffer[1024];
	ssize_t	n;

	while (cmds->next)
	{
		pipe(fd);
		pid = fork();
		if(pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], STD_OUT);
			close(fd[1]);
			check_is_buildin(cmds->args, shell);
			exit(1);
		}
		else
		{
			close(fd[1]);
			while ((n = read(fd[0], buffer, sizeof(buffer)-1)) > 0)
			{
				buffer[n] = '\0';
				printf("Parent received: %s", buffer);
			}
			close(fd[0]);
			wait(0);
		}
		cmds = cmds->next;
	}
	return (0);
}
