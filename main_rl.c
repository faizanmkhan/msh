#include "minishell.h"

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
		printf("input: %s\n", input);
		args = ft_split(input, ' ');
		free(input);
	}
	//args = malloc(sizeof(char *) * argc);
	if (!args)
		return (free(shell->current_dir), free(shell), 1);
	//return_code = check_is_buildin(args, shell);
	return_code = check_for_operators(args, shell);
	free(args);
	free(shell->current_dir);
	free(shell);
	return (return_code);
}
