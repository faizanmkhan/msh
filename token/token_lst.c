/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:46:49 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

t_tok	*new_tok(char *str, char *str_cpy, int type, int status)
{
	t_tok	*new_tok;

	new_tok = malloc(sizeof(t_tok));
	if (!(new_tok))
		return (NULL);
	new_tok->type = type;
	new_tok->data = str;
	new_tok->data_cpy = str_cpy;
	new_tok->has_var = false;
	new_tok->status = status;
	new_tok->join = false;
	new_tok->prv = NULL;
	new_tok->nxt = NULL;
	return (new_tok);
}

void	add_back_tok(t_tok **head, t_tok *new_tok)
{
	t_tok	*tmp;

	tmp = *head;
	if (tmp == NULL)
		*head = new_tok;
	else if (head && *head && new_tok)
	{
		while (tmp->nxt)
			tmp = tmp->nxt;
		tmp->nxt = new_tok;
		new_tok->prv = tmp;
	}
	return ;
}

void	del_tok(t_tok *tok_to_del, void (*del)(void *))
{
	if (del && tok_to_del && tok_to_del->data)
	{
		(*del)(tok_to_del->data);
		tok_to_del->data = NULL;
	}
	if (del && tok_to_del && tok_to_del->data_cpy)
	{
		(*del)(tok_to_del->data_cpy);
		tok_to_del->data_cpy = NULL;
	}
	if (tok_to_del->prv)
		tok_to_del->prv->nxt = tok_to_del->nxt;
	if (tok_to_del->nxt)
		tok_to_del->nxt->prv = tok_to_del->prv;
	free_ptr(tok_to_del);
}

void	del_all_toks(t_tok **head, void (*del)(void *))
{
	t_tok	*tmp;

	while (*head)
	{
		tmp = (*head)->nxt;
		del_tok(*head, del);
		*head = tmp;
	}
}
