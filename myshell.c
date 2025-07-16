/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:17:43 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:52 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/myshell.h"

int	g_exit_code;

void	exit_minishell(t_appdata *appdata, int exit_code)
{
	int	restore_fds;
	int	clean_history;

	if (appdata)
	{
		if (appdata->head_cmd && appdata->head_cmd->fds)
		{
			restore_fds = true;
			close_fds(appdata->head_cmd, restore_fds);
		}
		clean_history = true;
		free_appdata(appdata, clean_history);
	}
	exit(exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_appdata	appdata;

	ft_memset(&appdata, 0, sizeof(t_appdata));
	if (!init_appdata(&appdata, argc, argv, envp))
		exit_minishell(NULL, EXIT_FAILURE);
	while (true)
	{
		set_signals_for_parsing();
		appdata.input = readline(PROMPT);
		set_signals_for_execution();
		if (parse_user_input(&appdata))
		{
			if (valid_appdata(&appdata))
				g_exit_code = execute(&appdata);
		}
		else
			g_exit_code = 1;
		free_appdata(&appdata, false);
	}
	exit_minishell(&appdata, g_exit_code);
	return (0);
}
