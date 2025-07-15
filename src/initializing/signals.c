#include "../../include/myshell.h"

static void	signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	signal_print_newline(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
}

static void	ignore_sigquit(void)
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
