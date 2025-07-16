/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:07:43 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 13:36:37 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

static	int	setup_input_redirection(t_cmd *cmd)
{
	int	fd;

	if (cmd->in_file)
	{
		fd = open(cmd->in_file, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->in_file);
			return (-1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return (0);
}

static	int	setup_output_redirection(t_cmd *cmd)
{
	int	fd;

	if (cmd->out_file)
	{
		if (cmd->append_mode)
			fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(cmd->out_file);
			return (-1);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return (0);
}

int	setup_redirections(t_cmd *cmd)
{
	if (setup_heredoc(cmd) == -1)
		return (-1);
	if (setup_input_redirection(cmd) == -1)
		return (-1);
	if (setup_output_redirection(cmd) == -1)
		return (-1);
	return (0);
}
