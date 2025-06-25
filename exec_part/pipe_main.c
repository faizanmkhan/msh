#include "../../tokenPars_part/myshell.h""

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

// Splits a string by a delimiter and trims whitespace
char **split_pipeline(const char *line)
{
	int count = 0;
	char **cmds = NULL;
	char *copy = strdup(line);
	char *token;
	char *saveptr = NULL;

	token = strtok_r(copy, "|", &saveptr);
	while (token)
	{
		cmds = realloc(cmds, sizeof(char *) * (count + 2));
		cmds[count++] = strdup(token);
		token = strtok_r(NULL, "|", &saveptr);
	}
	if (cmds)
		cmds[count] = NULL;

	free(copy);
	return cmds;
}

char **split_args(const char *cmd)
{
	int count = 0;
	char **args = NULL;
	char *token;
	char *copy = strdup(cmd);
	char *saveptr = NULL;

	token = strtok_r(copy, " \t\n", &saveptr);
	while (token)
	{
		args = realloc(args, sizeof(char *) * (count + 2));
		args[count++] = strdup(token);
		token = strtok_r(NULL, " \t\n", &saveptr);
	}
	if (args)
		args[count] = NULL;

	free(copy);
	return args;
}

t_cmd *create_cmd(const char *cmd_str)
{
	t_cmd *cmd = calloc(1, sizeof(t_cmd));
	if (!cmd)
		return NULL;

	cmd->args = split_args(cmd_str);
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append_mode = 0;
	cmd->heredoc_delimiter = NULL;
	cmd->next = NULL;
	return cmd;
}

void free_cmds(t_cmd *head)
{
	t_cmd *tmp;
	while (head)
	{
		tmp = head->next;
		for (int i = 0; head->args && head->args[i]; i++)
			free(head->args[i]);
		free(head->args);
		free(head);
		head = tmp;
	}
}

int main(void)
{
	t_shell_data *shell = malloc(sizeof(t_shell_data));
	if (!shell)
		return 1;

	shell->saved_stdin = dup(STD_IN);
	shell->saved_stdout = dup(STD_OUT);
	shell->current_dir = malloc(1024);
	if (!shell->current_dir || !getcwd(shell->current_dir, 1024))
	{
		perror("shell init");
		free(shell->current_dir);
		free(shell);
		return 1;
	}

	char *line;
	while ((line = readline("my_shell> ")) != NULL)
	{
		if (*line)
			add_history(line);

		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}

		char **pipeline_cmds = split_pipeline(line);
		if (!pipeline_cmds)
		{
			free(line);
			continue;
		}

		t_cmd *head = NULL;
		t_cmd *curr = NULL;

		for (int i = 0; pipeline_cmds[i]; i++)
		{
			t_cmd *new_cmd = create_cmd(pipeline_cmds[i]);
			if (!new_cmd)
				continue;
			if (!head)
				head = new_cmd;
			else
				curr->next = new_cmd;
			curr = new_cmd;
			free(pipeline_cmds[i]);
		}
		free(pipeline_cmds);

		check_cmd(head, shell);
		reset_redir(shell);
		free_cmds(head);
		free(line);
	}

	free(shell->current_dir);
	free(shell);
	return 0;
}


/*#include "../../tokenPars_part/myshell.h""

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

char **split_args(const char *cmd)
{
	int count = 0;
	char **args = NULL;
	char *token;
	char *copy = strdup(cmd);
	char *saveptr = NULL;

	token = strtok_r(copy, " ", &saveptr);
	while (token)
	{
		args = realloc(args, sizeof(char *) * (count + 2));
		args[count] = strdup(token);
		count++;
		token = strtok_r(NULL, " ", &saveptr);
	}
	if (args)
		args[count] = NULL;

	free(copy);
	return args;
}

t_cmd *create_cmd(const char *cmd_str)
{
	t_cmd *cmd = calloc(1, sizeof(t_cmd));
	if (!cmd)
		return NULL;

	cmd->args = split_args(cmd_str);
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append_mode = 0;
	cmd->heredoc_delimiter = NULL;
	cmd->next = NULL;
	return cmd;
}

void free_cmds(t_cmd *head)
{
	t_cmd *tmp;
	while (head)
	{
		tmp = head->next;
		for (int i = 0; head->args && head->args[i]; i++)
			free(head->args[i]);
		free(head->args);
		free(head);
		head = tmp;
	}
}

int main(void)
{
	//int	saved_stdin;
	//int	saved_stdout;
    t_shell_data *shell = malloc(sizeof(t_shell_data));
    if (!shell)
        return 1;

	shell->saved_stdin = dup(STD_IN);
	shell->saved_stdout = dup(STD_OUT);
    shell->current_dir = malloc(1024);
    if (!shell->current_dir)
    {
        free(shell);
        return 1;
    }
    if (getcwd(shell->current_dir, 1024) == NULL)
    {
        perror("getcwd");
        free(shell->current_dir);
        free(shell);
        return 1;
    }

    char *line;
    while ((line = readline("my_shell> ")) != NULL)
    {
        if (*line)
            add_history(line);

        if (strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }

        t_cmd *user_cmd = create_cmd(line);
        if (!user_cmd)
        {
            fprintf(stderr, "Error creating command\n");
            free(line);
            continue;
        }

        // Run the command
        check_cmd(user_cmd, shell);
	reset_redir(shell);
	//dup2(shell->saved_stdin, STD_IN);
	//dup2(shell->saved_stdout, STD_OUT);
        free_cmds(user_cmd);
        free(line);
    }

    free(shell->current_dir);
    free(shell);
    return 0;
}*/
