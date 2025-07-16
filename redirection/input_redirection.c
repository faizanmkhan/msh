/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:15:16 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

bool	remove_input_file_ref(t_fds *fds)
{
	if (fds->input_file)
	{
		if (fds->fd_in == -1 || (fds->output_file && fds->fd_out == -1))
			return (false);
		if (fds->heredoc_delim != NULL)
		{
			unlink(fds->input_file);
			free_ptr(fds->heredoc_delim);
		}
		wrapper_close_pipe(&fds->fd_in);
		free_ptr(fds->input_file);
	}
	return (true);
}

bool	remove_output_file_ref(t_fds *fds)
{
	if (fds->output_file)
	{
		if (fds->fd_out == -1 || (fds->input_file && fds->fd_in == -1))
			return (false);
		free_ptr(fds->output_file);
		wrapper_close_pipe(&fds->fd_out);
	}
	return (true);
}

static void	open_input_file(t_fds *fds, char *filename, char *filename_cpy)
{
	if (!remove_input_file_ref(fds))
		return ;
	fds->input_file = ft_strdup(filename);
	if (fds->input_file && fds->input_file[0] == '\0')
	{
		ft_print_cmd_error(filename_cpy, NULL, "ambiguous redirect", 0);
		return ;
	}
	fds->fd_in = open(fds->input_file, O_RDONLY);
	if (fds->fd_in == -1)
		ft_print_cmd_error(fds->input_file, NULL, strerror(errno), 0);
}

void	parse_input_redirection(t_cmd **head_cmd, t_tok **head_tok)
{
	t_cmd	*cmd;

	cmd = last_cmd(*head_cmd);
	init_fds(cmd);
	open_input_file(cmd->fds, (*head_tok)->nxt->data,
		(*head_tok)->nxt->data_cpy);
	if ((*head_tok)->nxt->nxt)
		*head_tok = (*head_tok)->nxt->nxt;
	else
		*head_tok = (*head_tok)->nxt;
}
