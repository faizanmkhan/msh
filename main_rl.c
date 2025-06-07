#include "minishell.h"

int	main(void)
{
	t_shell	*shell;
	char	**args;
	char	**env_paths;
	int		return_code;
	int		i;
	int		*pipes;
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
		pipes = pipe_counter(input);
		//piped_commands(pipes, input); // test
		if (pipes != NULL)
		{	
			piped_commands(pipes, input);
			
		}
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

int	mem_cleaner(char **args, int *pipes, t_shell *shell, )
{
	int	i;

	if (args)

	while (args)	
	free(shell->current_dir);
	free(shell);
}
