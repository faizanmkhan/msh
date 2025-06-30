#include "myshell.h"

int	command_execution(t_shell_data *myshell)
{
	t_cmd *cmd;
	
	cmd = myshell->head_cmd;
	if (!cmd)
		return (0);
	if(!cmd->next)
		return (execute_sigle_cmd(myshell));
	else
		return (execute_pipeline(myshell));
}

int execute_sigle_cmd(t_shell_data *myshell)
{
	int status;
	char *exectable;

	if (!myshell->head_cmd->args || !myshell->head_cmd->args[0])
		return (0);
	if (is_builtin(myshell->head_cmd->args[0]))
		return (execute_builtin(myshell, myshell->head_cmd));
	
}