#include "minishell.h"


int	pipe_counter(char *str);

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
		printf("pipes check count: %d\n", pipe_counter(input));
		args = ft_split(input, ' ');
		free(input);
		if (!args)
			return (free(shell->current_dir), free(shell), 1);
		return_code = check_for_operators(args, shell);
		free(args);
		if (return_code == -2)
			break ;
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

int	pipe_counter(char *str)
{
	int	i;
	int	occur_c;
	int	valid_pipes;
	int	s_quotes_c;
	int	d_quotes_c;

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
	return (valid_pipes);
}
