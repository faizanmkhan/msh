#include "../minishell.h"
int	reset_redir(t_shell *shell)
{
	int	in;
	int	out;

	in = dup2(shell->saved_stdin, STD_IN);
	out = dup2(shell->saved_stdout, STD_OUT);
	if (in > 0 && out > 0)
		return (0);
	else
		return (-1);
}

int	input_redir(t_cmd *cmd, t_shell *shell)
{
	int		fd;

	fd = open(cmd->input_file, O_RDONLY);
	if (fd < 0)
		return(-1); //ERROR
	dup2(fd, STD_IN);
	close(fd);
	return (0);
}

int	output_redir(t_cmd *cmd, t_shell *shell, int append_mode)
{
	int		fd;

	if (append_mode == 0)
		fd = open(cmd->output_file, O_CREAT | O_RDWR, 0644);	
	else
		fd = open(cmd->output_file, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fd < 0)
		return (-1); //ERROR
	dup2(fd, STD_OUT);
	close(fd);
	return (0);
}

int	heredoc_run(char *delimiter)
{

}
