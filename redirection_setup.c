#include "myshell.h"

static int handle_heredoc(t_cmd *cmd)
{
	char *line;
	int pipefd[2];

	if (!cmd->heredoc_delim)
		return (0);
	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, cmd->heredoc_delim) == 0)
		{
			free(line);
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (0);
}

static int setup_heredoc(t_cmd *cmd)
{
	if (cmd->heredoc_delim)
	{
		if (handle_heredoc(cmd) == -1)
			return (-1);
	}
	return 0;
}

static int setup_input_redirection(t_cmd *cmd)
{
	int fd;

	if (cmd->in_file)
	{
		fd = open(cmd->in_file, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->in_file);
			return -1;
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return 0;
}

static int setup_output_redirection(t_cmd *cmd)
{
	int fd;

	if (cmd->out_file)
	{
		if (cmd->append_mode)
			fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd == -1)
		{
			perror(cmd->out_file);
			return -1;
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return 0;
}

int setup_redirections(t_cmd *cmd)
{
	if (setup_heredoc(cmd) == -1)
		return (-1);

	if (setup_input_redirection(cmd) == -1)
		return (-1);

	if (setup_output_redirection(cmd) == -1)
		return (-1);

	return (0);
}
