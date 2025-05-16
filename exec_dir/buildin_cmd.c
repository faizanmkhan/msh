#include "../minishell.h"

//TODOS
//1. Support for absolute path eg. (/bin/dir1/child_dir/filename.file
//2. Strict error handling 
//3. Freeing mem
//4. 'global' variable support for export and unset functions.
//5. Actually kill cmd i guess (kill_all func, that kills each pid from pid array in struct maybe??)

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
		return (chdir("/home/kacper/"));
	else if (ft_strncmp(cmds[0], "pwd", 3) == 0)
		return (perform_buildin(cmds, path));
	else if (ft_strncmp(cmds[0], "export", 6) == 0)
		return (perform_buildin(cmds, path));
	else if (ft_strncmp(cmds[0], "unset", 5) == 0)
		return (perform_buildin(cmds, path));
	else if (ft_strncmp(cmds[0], "env", 3) == 0)
		return (perform_buildin(cmds, path));
	//else if (ft_strncmp(cmds[0], "exit", 4) == 0)
		//return (kill()); //
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

