/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:07:34 by korzecho          #+#    #+#             */
/*   Updated: 2025/07/01 17:07:36 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

int	reset_redir(t_shell_data *shell)
{
	int	in;
	int	out;

	in = dup2(shell->saved_stdin, STDIN_FILENO);
	out = dup2(shell->saved_stdout, STDOUT_FILENO);
	if (in > 0 && out > 0)
		return (0);
	else
		return (-1);
}
