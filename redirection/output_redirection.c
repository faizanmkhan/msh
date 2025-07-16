/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:14:37 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

static void	open_outfile_trunc(t_fds *fds, char *filename, char *filename_cpy)
{
	if (!remove_output_file_ref(fds))
		return ;
	fds->output_file = ft_strdup(filename);
	if (fds->output_file && fds->output_file[0] == '\0')
	{
		ft_print_cmd_error(filename_cpy, NULL, "ambiguous redirect", 0);
		return ;
	}
	fds->fd_out = open(fds->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fds->fd_out == -1)
		ft_print_cmd_error(fds->output_file, NULL, strerror(errno), 0);
}

void	parse_output_redirection(t_cmd **head_cmd, t_tok **head_tok)
{
	t_cmd	*cmd;

	cmd = last_cmd(*head_cmd);
	init_fds(cmd);
	open_outfile_trunc(cmd->fds, (*head_tok)->nxt->data,
		(*head_tok)->nxt->data_cpy);
	if ((*head_tok)->nxt->nxt)
		*head_tok = (*head_tok)->nxt->nxt;
	else
		*head_tok = (*head_tok)->nxt;
}
