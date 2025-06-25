#include "../../tokenPars_part/myshell.h"

void	fork_child(int *pipefd, int prev_pipe_read, t_cmd *cmd, t_shell_data *shell)
{
	if (shell->cmd_index != 0) //if this cmd isn't 1st cmd redirect INPUT to the last cmd output, otherwise ignore check and read from normal STDIN
	{
		dup2(prev_pipe_read, STD_IN);
		close (prev_pipe_read);
	}
	if (cmd->next) //if cmd isn't the last cmd redirect OUTPUT of the cmd to the pipe
	{
		close(pipefd[0]);
		dup2(pipefd[1], STD_OUT);
		close(pipefd[1]);
	}
	check_is_buildin(cmd->args, shell); //check_is_buildin checks also for external cmds if no buildin matches, runs execv() so it replaces this procces and on succes will end o this line
	exit (EXIT_FAILURE); //otherwise exit with the cmd running failure
}

t_cmd	*fork_parent(int *pipefd, t_cmd *cmd,
		int *prev_pipe_read, t_shell_data *shell)
{
	if (shell->cmd_index != 0) //if not the 1st cmd
		close(*prev_pipe_read);
	if (cmd->next) // if not the last cmd
	{
		close(pipefd[1]);//parent only reads so no write end needed
		*prev_pipe_read = pipefd[0]; //save prev_pipe_read to be able to retrive information from this read end on next loop iteration (because pipefd[] is locally created in loop)
	}
	else
		*prev_pipe_read = -1;
	shell->cmd_index++;
	return (cmd->next);// this is basically increment in the loop that is based on checking if cmd isn't NULL
}

int	pipe_loop(t_cmd *cmd, t_shell_data *shell)
{
	int		pipefd[2];
	int		prev_pipe_read;
	int		status;
	pid_t	pid;

	prev_pipe_read = -1; //copy of the read end of the pipe from previous cmd output
	shell->cmd_index = 0; //index of the cmd to avoid wrong redirectin for the first cmd
	while (cmd)
	{
		if (cmd->next)
			if (pipe(pipefd) == -1) //create a pipe
				return (-1);
		pid = fork();
		if (pid == -1)
			return (-1); //ERROR
		if (pid == 0)
			fork_child(pipefd, prev_pipe_read, cmd, shell);
		else
			cmd = fork_parent(pipefd, cmd, &prev_pipe_read, shell);
	}
	while (wait(&status) > 0) //wait for every child to finish for safety to prevent zombie processes
		;
	return (0);
}
