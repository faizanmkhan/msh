/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:34:37 by korzecho          #+#    #+#             */
/*   Updated: 2025/07/16 13:41:34 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

static	char	*heredoc_loop(t_cmd *cmd, int *pipefd)
{
	char	*line;
	char	*file;

	file = ft_strdup("");
	if (!file)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, cmd->heredoc_delim) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		line = ft_strjoin(line, "\n");
		file = ft_strjoin(file, line);
		free(line);
	}
	return (file);
}

static int	handle_heredoc(t_cmd *cmd)
{
	char	*file;
	int		pipefd[2];
	int		fd;

	if (!cmd->heredoc_delim)
		return (0);
	if (pipe(pipefd) == -1)
		return (-1);
	file = ft_strdup("");
	if (!file)
		return (-1);
	file = heredoc_loop(cmd, pipefd);
	fd = open(cmd->heredoc_delim, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd <= 0)
	{
		printf("ERROR\n");
		free(file);
		return (-1);
	}
	write(fd, file, ft_strlen(file));
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (0);
}

int	setup_heredoc(t_cmd *cmd)
{
	if (cmd->heredoc_delim)
	{
		if (handle_heredoc(cmd) == -1)
			return (-1);
	}
	return (0);
}
