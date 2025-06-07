#include "minishell.h"


int	*pipe_counter(char *str);
int	piped_commands(int *pipes, char *input);
char	*clear_str(char *str);

int	main(void)
{
	t_shell	*shell;
	char	**args;
	char	**env_paths;
	int		return_code;
	int		i;
	char	*input;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	shell->current_dir = malloc(sizeof(char) * 1024);
	if (!shell->current_dir)
		return (free(shell), 1);
	getcwd(shell->current_dir, 1024);
	while (1)
	{
		input = readline("my_shell> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		//printf("pipes check count: %d\n", piped_commands(pipe_counter(input), input));
		int *pipes = pipe_counter(input);
		//piped_commands(pipes, input); // test
		if (pipes != NULL)
			piped_commands(pipes, input);
		else
		{
			args = ft_split(input, ' ');
			free(input);
			if (!args)
				return (free(shell->current_dir), free(shell), 1);
			return_code = check_for_operators(args, shell);
			free(args);
			if (return_code == -2)
				break ;
		}
	}
	//args = malloc(sizeof(char *) * argc);
	free(shell->current_dir);
	free(shell);
	if (return_code == -2)
		return(0);
	return (return_code);
}

char	*check_operator(char *input)
{
	//count pipes
	//check for input redirection <
	//check for output redirection >, >>
	//check for heredoc <<XYZ
	//check for '$' characters
	
	pipe_counter(input);
}

char	*clear_str(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*dst;

	i = 0;
	j = 0;
	while (str[i] && (!ft_isprint(str[i]) || str[i] == ' '))
		i++;
	len = ft_strlen(str) - i;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		perror("ERROR");
	while(str[i])
		dst[j++] = str[i++];
	dst[j] = '\0';
	free(str);
	return (dst);
}

int	piped_commands(int *pipes, char *input)
{
	char	**cmds;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 1;
	while (pipes[len])
		len++;
	//printf("len: %d, pipe 2: %d\n", len, pipes[2]);
	cmds = (char **)malloc(sizeof(char *) * (len + 2));
	//cmds[i + 2] = 0;
	//i = 0;
	while (i < len - 1)
	{
		if (i == 0)
			cmds[i] = ft_substr(input, pipes[i], pipes[i + 1] - pipes[i]);
		else	
			cmds[i] = ft_substr(input, pipes[i] + 1, pipes[i + 1] - pipes[i] - 1);
		cmds[i] = clear_str(cmds[i]);
		printf("%s\n", cmds[i]);
		i++;
	}
	cmds[i] = NULL;
	return (i);
}

int	*pipe_counter(char *str)
{
	int	i;
	int	occur_c;
	int	valid_pipes;
	int	s_quotes_c;
	int	d_quotes_c;
	int	*pipes_index;

	s_quotes_c = 0;
	d_quotes_c = 0;
	i = 0;
	valid_pipes = 0;
	while (str[i])
	{
		if (str[i] == 34)
			d_quotes_c++;
		else if (str[i] == 39)
			s_quotes_c++;
		else if (str[i] == '|')
		{
			if (d_quotes_c % 2 == 0 && s_quotes_c % 2 == 0)
				valid_pipes++;
		}
		i++;	
	}
	if (valid_pipes == 0)
		return (NULL);
	pipes_index = (int *)malloc(sizeof(int) * (valid_pipes + 3));
	pipes_index[0] = 0;
	i = 0;
	s_quotes_c = 0;
	d_quotes_c = 0;
	int j = 1;
	while (str[i])
	{
		if (str[i] == 34)
			d_quotes_c++;
		else if (str[i] == 39)
			s_quotes_c++;
		else if (str[i] == '|')
		{
			if (d_quotes_c % 2 == 0 && s_quotes_c % 2 == 0)
				pipes_index[j++] = i;
		}
		i++;	
	}
	pipes_index[j++] = i;
	pipes_index[j] = 0;
	return (pipes_index);
}
