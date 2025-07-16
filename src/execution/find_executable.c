/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:07:32 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 13:07:33 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

static char	*check_direct_path(char *command)
{
	if (strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	return (NULL);
}

static	char	*join_path_command(const char *path, const char *command)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, command);
	free(tmp);
	return (full_path);
}

static	int	is_executable(const char *full_path)
{
	struct stat	st;

	if (stat(full_path, &st) == 0
		&& S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
		return (1);
	return (0);
}

static	char	*search_in_path(char **paths, char *command)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = join_path_command(paths[i], command);
		if (!full_path)
		{
			i++;
			continue ;
		}
		if (is_executable(full_path))
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

char	*find_executable(t_shell_data *shell, char *command)
{
	char	*result;
	char	*path_env;
	char	**paths;

	result = check_direct_path(command);
	if (result)
		return (result);
	path_env = get_env_value(shell, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_path(paths, command));
}
