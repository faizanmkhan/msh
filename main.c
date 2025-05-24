#include "minishell.h"

int main(int argc, char **argv)
{
	int	return_code;
    char **a;
    int i;
	t_shell	*shell;

	return_code = 0;
	shell = (t_shell *)malloc(sizeof(t_shell));
	shell->current_dir = (char *)malloc(sizeof(char) * 1024);
	getcwd(shell->current_dir, 1024);
	// Skip if there are no arguments besides program name
    if (argc < 2)
    {
        printf("Usage: %s <command> [args...]\n", argv[0]);
        return (1);
    }

    // Allocate space for all arguments except program name, plus NULL terminator
    a = (char **)malloc(sizeof(char *) * argc);
    if (!a)
        return (1);

    // Copy argv[1] ... argv[argc-1] into a[0] ... a[argc-2]
    for (i = 1; i < argc; i++)
        a[i - 1] = argv[i];
    a[argc - 1] = NULL; // NULL-terminate

    char **l = get_env_paths();
    return_code = check_is_buildin(a, shell); 

    i = 0;

    while (l[i])
		i++;
    	while (i >= 0)
		free(l[i--]);
	free(l);
    free(a);
    free(shell->current_dir);
    free(shell);
    return (return_code);
}
