/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:46:43 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

int	ft_chdir(char *path)
{
	int		status;
	char	*error;

	status = chdir(path);
	if (status == -1)
	{
		error = strerror(errno);
		ft_putendl_fd(error, STDERR_FILENO);
	}
	return (status);
}

char	*find_path(char **envp, char *cmd, int i)
{
	char	**paths;
	char	*path;
	char	*tmp_path;

	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (!access(path, F_OK))
		{
			ft_free_tab(paths);
			return (path);
		}
		free(path);
	}
	ft_free_tab(paths);
	return (0);
}

int	check_command_not_found(t_cmd *cmd, int code)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd->name, &cmd_stat);
	if (S_ISDIR(cmd_stat.st_mode))
		return (ft_print_cmd_error(cmd->name, NULL, "Is a directory", 126));
	if (!ft_strchr(cmd->name, '/') && code != -1)
		return (ft_print_cmd_error(cmd->name, NULL, "command not found", 127));
	if (access(cmd->name, F_OK) != 0)
		return (ft_print_cmd_error(cmd->name, NULL, strerror(errno), 127));
	if (access(cmd->name, F_OK | X_OK) != 0)
		return (ft_print_cmd_error(cmd->name, NULL, strerror(errno), 126));
	return (EXIT_SUCCESS);
}

int	valid_command(t_cmd *cmd, int *exit_code)
{
	int	temp;

	temp = *exit_code;
	if (!cmd || !cmd->name)
	{
		if (cmd && cmd->fds)
			temp = valid_fds(cmd->fds);
		else
			temp = BAD;
	}
	*exit_code = temp;
	return (temp);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}
