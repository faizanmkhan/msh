/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:36:07 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free_ptr(tab[i]);
	free(tab);
}

void	free_str_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = -1;
		while (tab[++i])
		{
			free_ptr(tab[i]);
			tab[i] = NULL;
		}
		free(tab);
		tab = NULL;
	}
}

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

int	ft_is_whitespace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_only_whitespace(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (!ft_is_whitespace(input[i]))
			return (0);
	}
	return (1);
}
