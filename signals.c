#include "myshell.h"

static void interupter_handler(int sig)
{
	g_signal = sig;
	
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void set_signals(t_shell_data *myshell)
{
	struct sigaction sa;

	g_signal = 0;
	myshell->exit_status = g_signal;
	sa.sa_handler = interupter_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
