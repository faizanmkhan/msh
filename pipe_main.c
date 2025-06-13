#include "minishell.h"

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
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STD_IN);
	saved_stdout = dup(STD_OUT);
    t_shell *shell = malloc(sizeof(t_shell));
    if (!shell)
        return 1;

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
	dup2(saved_stdin, STD_IN);
	dup2(saved_stdout, STD_OUT);
        free_cmds(user_cmd);
        free(line);
    }

    free(shell->current_dir);
    free(shell);
    return 0;
}
