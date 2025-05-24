#include "../minishell.h"

int	check_for_cmd(char **cmds, char *path)
{
	pid_t	pid;
	char	*complete_path;
	char	*temp;

	temp = ft_strjoin(path, "/");
	complete_path = ft_strjoin(temp, cmds[0]);
	free(temp);
	if (!complete_path)
		return (-1);
	if (access(complete_path, X_OK) == -1)
	{
		free(complete_path);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		free(complete_path);
		return (-1);
	}
	else if (pid == 0)
	{
		execv(complete_path, cmds);
	}
	//else
	//{
		//
	//}
	free(complete_path);
	return (0);
}

char	**get_env_paths(void)
{
	char	*str;
	char	**a;
	int		i;

	i = 0;
	a = ft_split(str, ':');
	str = getenv("PATH");
	if (a == NULL)
		perror("ERROR!");
	while (a[i])
		i++;
	return (a);
}

int	external_cmd_exec(char **args, char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (check_for_cmd(args, paths[i]) == 0)
			return (0);
		i++;
	}
	return (-1);
}
