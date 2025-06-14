#include "../minishell.h"

int	check_is_buildin(char **cmds, t_shell *shell)
{
	char	*path;

	if (!cmds || !cmds[0] || !shell || !shell->current_dir)
		return (-1);
	if (ft_strncmp(cmds[0], "echo", 4) == 0)
		return (ft_echo(cmds));
	else if (ft_strncmp(cmds[0], "cd", 2) == 0)
		return (ft_cd(cmds[1], shell));
	else if (ft_strncmp(cmds[0], "pwd", 3) == 0)
		return (ft_pwd(cmds, shell));
	//else if (ft_strncmp(cmds[0], "export", 6) == 0)
	//	return (perform_buildin(cmds, path));
	//else if (ft_strncmp(cmds[0], "unset", 5) == 0)
	//	return (perform_buildin(cmds, path));
	//else if (ft_strncmp(cmds[0], "env", 3) == 0)
	//	return (perform_buildin(cmds, path));
	else if (ft_strncmp(cmds[0], "exit", 4) == 0)
		return (-2);
	else if (external_cmd_exec(cmds, get_env_paths()) == 0)
		return (0);
	else
		printf("Command not found\n");
	return (-1);
}
