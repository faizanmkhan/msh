/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:50:15 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 21:09:58 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

void	signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_print_newline(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
}

void	ignore_sigquit(void)
{
	struct sigaction	sig;

	ft_bzero(&sig, sizeof(sig));
	sig.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig, NULL);
}

void	set_signals_for_execution(void)
{
	struct sigaction	sig;

	ft_bzero(&sig, sizeof(sig));
	sig.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

void	set_signals_for_parsing(void)
{
	struct sigaction	sig;

	ignore_sigquit();
	ft_bzero(&sig, sizeof(sig));
	sig.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &sig, NULL);
}
