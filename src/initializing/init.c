/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:09:15 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 13:09:16 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

void	init_shell_data(t_shell_data *myshell, char **envp)
{
	int			i;
	t_env_data	*env_var;

	myshell->exit_status = 0;
	myshell->envp = envp;
	myshell->pid = -1;
	myshell->head_cmd = NULL;
	myshell->head_token = NULL;
	myshell->shell_env = NULL;
	myshell->syntax_err = 0;
	i = 0;
	while (envp[i])
	{
		env_var = parse_env_var(envp[i]);
		if (env_var)
			append_env_vars(myshell, env_var);
		i++;
	}
}

void	core_shell_loop(t_shell_data *myshell)
{
	char	*input;

	while (42)
	{
		set_signals_for_parsing();
		input = readline("mY_sHEll:~$ ");
		set_signals_for_execution();
		if (!input)
		{
			printf("exit\n");
			free (input);
			break ;
		}
		if (g_signal == SIGQUIT)
		{
			myshell->exit_status = 130;
			g_signal = 0;
		}
		if (input)
		{
			managing_input(myshell, input);
			myshell->exit_status = command_execution(myshell);
			if (myshell->head_cmd && myshell->head_cmd->heredoc_delim)
				unlink(myshell->head_cmd->heredoc_delim);
			myshell->syntax_err = 0;
			free_token(myshell->head_token);
			free_commands(myshell->head_cmd);
		}
		free (input);
	}
}
