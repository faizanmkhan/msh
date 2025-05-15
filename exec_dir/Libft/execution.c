#include <stdlib.h>
#include "Libft/srcs/libft.h"
#include <unistd.h>
#include <stdio.h>

int	perform_buildin(char **cmds, char *path)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("fork failed");
	else if (pid == 0)
		execv(path, cmds);
	else
		printf("Parent\n");
}

int	check_is_buildin(char **cmds)
{
	char *path;
	
	if (!cmds || !cmds[0])
		return (-1);
	path = ft_strjoin("/bin/", cmds[0]);

	if (ft_strncmp(cmds[0], "echo", 4) == 0)
		return (perform_buildin(cmds, path));
	else if (ft_strncmp(cmds[0], "cd", 2) == 0)
		return (perform_buildin(cmds, path));
	else if (ft_strncmp(cmds[0], "pwd", 3) == 0)
		return (perform_buildin(cmds, path));
	else if (ft_strncmp(cmds[0], "export", 6) == 0)
		return (perform_buildin(cmds, path));
	//else if (ft_strcmp(cmds[0], "unset") == 0)
	//	return (perform_buildin(cmds, path));
	//else if (ft_strcmp(cmds[0], "env") == 0)
	//	return (perform_buildin(cmds, path));
	//else if (ft_strcmp(cmds[0], "exit") == 0)
	//	return (perform_buildin(cmds, path));
	else
		printf("Command not found\n");
	return (-1);
}

#include <stdlib.h>

int	main(int argc, char **argv)
{
	char **a;

	(void)argc; // Unused for now

	a = (char **)malloc(sizeof(char *) * 3);
	if (!a)
		return (1);

	a[0] = argv[1];  // Example: "./minishell" or whatever the binary name is
	a[1] = argv[2];
	a[2] = NULL;
	// NULL-terminate the array


	check_is_buildin(a);  // Assuming this checks if a[0] is a built-in command

	free(a);
	return (0);
}

