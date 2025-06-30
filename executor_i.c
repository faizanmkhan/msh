#include "myshell.h"

int	check_absolute_path(char **args)
{
	int	pid;

	if (access(args[0], X_OK) == -1)
	{
		return (-1);
	}
	printf("path: %s\n", args[0]);
	pid = fork();
	if (pid < 0)
	{
		return (-1);
	}
	else if (pid == 0)
		execv(args[0], args);
	return (0);

}

int	external_cmd_exec(char **args, char **paths) //paths already set using get_env_paths()
{
	int	i;

	if (args[0][0] == '/' || args[0][0] == '.') //checks if string starts with '/' or '.' to properly run for example: '/bin/ls' or './a.out' (this ./ is not working perfectly right now)
	{
		check_absolute_path(args); //TODO finish
		return (free_paths(paths));
	}
	i = 0;
	while (paths[i])
	{
		if (check_for_cmd(args, paths[i]) == 0)
			return (free_paths(paths));
		i++;
	}
	free_paths(paths);
	return (-1);
}