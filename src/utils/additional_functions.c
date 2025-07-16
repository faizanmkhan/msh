/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:00:26 by korzecho          #+#    #+#             */
/*   Updated: 2025/07/16 14:00:26 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return ((unsigned char)(*str1) - (unsigned char)(*str2));
}

void	syntax_error(t_shell_data *shell)
{
	ft_putstr_fd("syntax error unexpected input\n", STDERR_FILENO);
	shell->exit_status = 2;
	shell->syntax_err = 1;
	return ;
}
