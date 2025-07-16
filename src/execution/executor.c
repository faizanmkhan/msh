/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:07:27 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 13:07:27 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

int	command_execution(t_shell_data *myshell)
{
	t_cmd	*cmd;

	cmd = myshell->head_cmd;
	if (myshell->syntax_err == 1)
		return (0);
	if (!cmd)
		return (0);
	if (!cmd->next)
		return (execute_single_cmd(myshell));
	else
		return (execute_pipeline(myshell));
	return (0);
}
