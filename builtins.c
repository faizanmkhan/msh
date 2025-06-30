#include "myshell.h"

int is_builtin(char *command)
{
	if (!command)
		return (0);
	
	return (ft_strcmp(command, "echo") == 0 ||
			ft_strcmp(command, "cd") == 0 ||
			ft_strcmp(command, "pwd") == 0 ||
			ft_strcmp(command, "export") == 0 ||
			ft_strcmp(command, "unset") == 0 ||
			ft_strcmp(command, "env") == 0 ||
			ft_strcmp(command, "exit") == 0);
}

int execute_builtin(t_shell_data *shell, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd->args));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(shell, cmd->args));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(shell, cmd->args));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(shell, cmd->args));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(shell));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(shell, cmd->args));
	
	return (0);
}

int builtin_echo(char **args)
{
	int i = 1;
	int newline = 1;

	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");

	return (0);
}

int builtin_pwd(void)
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

int builtin_unset(t_shell_data *shell, char **args)
{
	int i = 1;

	while (args[i])
	{
		unset_env_value(shell, args[i]);
		i++;
	}

	return (0);
}

int builtin_env(t_shell_data *shell)
{
	t_env_data *current = shell->shell_env;

	while (current)
	{
		if (current->value && ft_strlen(current->value) > 0)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}

	return (0);
}

int builtin_exit(t_shell_data *shell, char **args)
{
	int exit_code = shell->exit_status;

	if (args[1])
	{
		exit_code = atoi(args[1]);
	}

	printf("exit\n");
	cleanup_shell(shell);
	exit(exit_code);
}

char *get_env_value(t_shell_data *shell, char *key)
{
	t_env_data *current;

	current = shell->shell_env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void set_env_value(t_shell_data *shell, char *key, char *value)
{
	t_env_data *current;
	t_env_data *new_env;

	current = shell->shell_env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return;
		}
		current = current->next;
	}
	new_env = malloc(sizeof(t_env_data));
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = shell->shell_env;
	shell->shell_env = new_env;
}

void unset_env_value(t_shell_data *shell, char *key)
{
	t_env_data *current;
	t_env_data *prev;

	current = shell->shell_env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				shell->shell_env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}
