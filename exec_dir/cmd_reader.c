#include "../minishell.h"

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

int	check_cmd(t_cmd *cmd, t_shell *shell)
{
	int	cmds;

	if (cmd->input_file)
	{
		input_redir(cmd, shell);
	}
	//else if (cmd->heredoc_delimiter)
		//heredoc_run(cmd->heredoc_delimiter);
	if (cmd->output_file)
		output_redir(cmd, shell, cmd->append_mode);
	cmds = count_cmds(cmd);
	if (cmds > 0)
		pipe_loop(cmd, shell);
	else
		check_is_buildin(cmd->args, shell);
	return (0);
}

int	perform_exec(t_cmd *cmd, t_shell *shell)
{
	int	cmds_count;
}
