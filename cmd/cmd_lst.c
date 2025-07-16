/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:48:05 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!(new_cmd))
		return (NULL);
	ft_memset(new_cmd, 0, sizeof(t_cmd));
	new_cmd->name = NULL;
	new_cmd->is_pipe_output = false;
	new_cmd->path = NULL;
	new_cmd->args = NULL;
	new_cmd->pipe_fd[0] = -1;
	new_cmd->pipe_fd[1] = -1;
	new_cmd->prv = NULL;
	new_cmd->nxt = NULL;
	return (new_cmd);
}

void	add_back_cmd(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	tmp = *head;
	if (!tmp)
		*head = new_cmd;
	else if (head && *head && new_cmd)
	{
		while (tmp->nxt)
			tmp = tmp->nxt;
		tmp->nxt = new_cmd;
		new_cmd->prv = tmp;
	}
}

t_cmd	*last_cmd(t_cmd *cmd)
{
	while (cmd->nxt != NULL)
		cmd = cmd->nxt;
	return (cmd);
}

void	del_cmd(t_cmd *cmd, void (*del)(void *))
{
	if (cmd->name)
		(*del)(cmd->name);
	if (cmd->args)
		free_str_tab(cmd->args);
	if (cmd->fds)
		free_fds(cmd->fds);
	(*del)(cmd);
}

void	del_all_cmds(t_cmd **head, void (*del)(void *))
{
	t_cmd	*tmp;

	while (*head != NULL)
	{
		tmp = (*head)->nxt;
		del_cmd(*head, del);
		*head = tmp;
	}
}
