#include "../../tokenPars_part/myshell.h"

int	count_cmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->next != NULL)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int	check_cmd(t_cmd *cmd, t_shell_data *shell) //cmd struct for args etc.
{
	int	cmds;

	//printf("in file: %s, out file: %s\n", cmd->in_file, cmd->out_file);
	if (cmd->in_file)
	{
		input_redir(cmd); //basically dup2 input
	}
	//else if (cmd->heredoc_delimiter)
		//heredoc_run(cmd->heredoc_delimiter);
	if (cmd->out_file)
		output_redir(cmd, cmd->append_mode); //basically dup2 output
	cmds = count_cmds(cmd);
	if (cmds > 0)
		pipe_loop(cmd, shell);//execute commands in the linked list order giving output as a input to next cmd, last cmd prints to STDIN (or redirected STDIN)
	else
		check_is_buildin(cmd->args, shell);//execute one cmd to STDIN (or redirected STDIN)
	return (0);
}
