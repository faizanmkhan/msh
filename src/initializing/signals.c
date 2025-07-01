/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:13:50 by korzecho          #+#    #+#             */
/*   Updated: 2025/07/01 20:29:30 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

static	void	interupter_handler(int sig)
{
	g_signal = sig;
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	quit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDIN_FILENO);
		exit(131);
	}
}

void	set_signals(t_shell_data *myshell)
{
	struct sigaction	sa;

	g_signal = 0;
	myshell->exit_status = g_signal;
	sa.sa_handler = interupter_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
