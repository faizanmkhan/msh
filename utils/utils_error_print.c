/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:35:01 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

char	*ft_strextend(char *str, char *extend)
{
	char	*tmp;

	if (!extend)
		return (str);
	if (!str)
		return (ft_strdup(extend));
	tmp = str;
	str = ft_strjoin(tmp, extend);
	free_ptr(tmp);
	return (str);
}

int	ft_print_cmd_error(char *cmd, char *cmd_arg, char *msg, int exit_code)
{
	char	*err_msg;
	int		arg_with_quotes;

	arg_with_quotes = (ft_strncmp(cmd, "export", 7) == 0 || ft_strncmp(cmd,
				"unset", 6) == 0);
	err_msg = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		err_msg = ft_strextend(err_msg, cmd);
		err_msg = ft_strextend(err_msg, ": ");
	}
	if (cmd_arg != NULL)
	{
		if (arg_with_quotes)
			err_msg = ft_strextend(err_msg, "`");
		err_msg = ft_strextend(err_msg, cmd_arg);
		if (arg_with_quotes)
			err_msg = ft_strextend(err_msg, "'");
		err_msg = ft_strextend(err_msg, ": ");
	}
	err_msg = ft_strextend(err_msg, msg);
	ft_putendl_fd(err_msg, STDERR_FILENO);
	free(err_msg);
	return (exit_code);
}

void	ft_print_error(char *msg, char *symbol, int quotes)
{
	char	*err_msg;

	err_msg = ft_strdup("minishell: ");
	err_msg = ft_strextend(err_msg, msg);
	if (quotes)
		err_msg = ft_strextend(err_msg, "`");
	else
		err_msg = ft_strextend(err_msg, ": ");
	err_msg = ft_strextend(err_msg, symbol);
	if (quotes)
		err_msg = ft_strextend(err_msg, "'");
	ft_putendl_fd(err_msg, STDERR_FILENO);
	free(err_msg);
}
