/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:32:59 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

int	wrapper_close(int fd)
{
	if (fd == -1)
		return (1);
	return (close(fd));
}

int	wrapper_close_pipe(int *fd)
{
	int		status;

	ft_bzero(&errno, sizeof(errno));
	if (*fd == -1)
		return (1);
	status = close((*fd));
	if (errno)
	{
		perror("Minishell: ");
		ft_putstr_fd("\n File descritor : ", STDERR_FILENO);
		ft_putnbr_fd(*fd, STDERR_FILENO);
		ft_putendl_fd("\n", STDERR_FILENO);
	}
	*fd = -1;
	return (status);
}

void	close_pipe_fds(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->pipe_fd[0])
		{
			wrapper_close_pipe(&cmd->pipe_fd[0]);
			wrapper_close_pipe(&cmd->pipe_fd[1]);
		}
		cmd = cmd->nxt;
	}
}

void	free_fds(t_fds *fds)
{
	if (!fds)
		return ;
	restore_fds(fds);
	if (fds->heredoc_delim)
	{
		unlink(fds->input_file);
		free_ptr(fds->heredoc_delim);
	}
	if (fds->input_file)
		free_ptr(fds->input_file);
	if (fds->output_file)
		free_ptr(fds->output_file);
	if (fds)
		free_ptr(fds);
}

void	close_fds(t_cmd *cmd, int with_restore)
{
	if (cmd->fds)
	{
		if (cmd->fds->fd_in != -1)
			wrapper_close_pipe(&cmd->fds->fd_in);
		if (cmd->fds->fd_out != -1)
			wrapper_close_pipe(&cmd->fds->fd_out);
		if (with_restore)
			restore_fds(cmd->fds);
	}
	close_pipe_fds(cmd);
}
