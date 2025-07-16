/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:26:22 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

void	parse_pipe(t_cmd **head_cmd, t_tok **head_tok)
{
	t_cmd	*cmd;

	cmd = last_cmd(*head_cmd);
	cmd->is_pipe_output = true;
	add_back_cmd(&cmd, new_cmd());
	*head_tok = (*head_tok)->nxt;
}
