#include "../minishell.h"

int	check_is_buildin(char **args, t_shell *shell)
{
	char	*path;

	if (!args || !args[0] || !shell || !shell->current_dir) //ERROR check
		return (-1);
	if (ft_strncmp(args[0], "echo", 4) == 0)
		return (ft_echo(args));
	else if (ft_strncmp(args[0], "cd", 2) == 0)
		return (ft_cd(args[1], shell));
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		return (ft_pwd(args, shell));
	//else if (ft_strncmp(args[0], "export", 6) == 0)
	//	return (perform_buildin(args, path));
	//else if (ft_strncmp(args[0], "unset", 5) == 0)
	//	return (perform_buildin(args, path));
	//else if (ft_strncmp(args[0], "env", 3) == 0)
	//	return (perform_buildin(args, path));
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		return (-2);
	else if (external_cmd_exec(args, get_env_paths()) == 0) //run external cmd execution
		return (0);
	else
		printf("Command not found\n");
	return (-1);
}
