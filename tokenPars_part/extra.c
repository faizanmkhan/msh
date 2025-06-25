//prototyping; ignore this file

void process_input(t_shell_data *myshell, char *input)
{
	(void)myshell;

	if(ft_isprint(*input))
	{
		if (!isspace(*input))
			add_history(input);
	}
	myshell->head_token = input_tokenaizer(input);
	//myshell->head_cmd = create_cmd_with_token(myshell); // need to code
	t_token *current = myshell->head_token;
	int i = 0;
	while(current)
	{
		printf("token %d: %s, type: %d\n", i, current->value, current->type);
		current = current->next;
		i++;
	}
}

void managing_input(t_shell_data *myshell, char *input)
{
	(void)myshell;

	if(ft_isprint(*input))
	{
		if (!isspace(*input))
			add_history(input);
	}
	myshell->head_token = input_tokenaizer(input);
	myshell->head_cmd = create_cmd_with_token(myshell);
	// test
	t_token *cur_tok;
	t_cmd	*cur_cmd;
	cur_tok = myshell->head_token;
	cur_cmd = myshell->head_cmd;
	int i = 0;
	while (cur_tok)
	{
		printf("token: %s, type: %d \n", cur_tok->value, cur_tok->type);
		if(cur_cmd->args)
		{
			printf("command: %s, file %s, mode: %d \n", cur_cmd->args[i], cur_cmd->in_file, cur_cmd->append_mode);
			cur_cmd = cur_cmd->next;
			i++;
		}
		cur_tok = cur_tok->next;
		i = 0;
	}
	
}