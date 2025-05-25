#include "minishell.h"

int	main(int argc, char **argv)
{
	t_shell	*shell;
	char	**args;
	char	**env_paths;
	int		return_code;
	int		i;

	if (argc < 2)
	{
		printf("Usage: %s <command> [args...]\n", argv[0]);
		return (1);
	}
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	shell->current_dir = malloc(sizeof(char) * 1024);
	if (!shell->current_dir)
		return (free(shell), 1);
	getcwd(shell->current_dir, 1024);
	args = malloc(sizeof(char *) * argc);
	if (!args)
		return (free(shell->current_dir), free(shell), 1);
	i = 1;
	while (i < argc)
	{
		args[i - 1] = argv[i];
		i++;
	}
	args[argc - 1] = NULL;
	return_code = check_is_buildin(args, shell);
	free(args);
	free(shell->current_dir);
	free(shell);
	return (return_code);
}
