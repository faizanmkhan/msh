#include "myshell.h"

int	command_execution(t_shell_data *myshell)
{
	t_cmd	*cmd;

	cmd = myshell->head_cmd;
	if (!cmd)
		return (0);
	if (!cmd->next)
		return (execute_single_cmd(myshell));
	else
		return (execute_pipeline(myshell));
	return (0);
}
