/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:14:56 by korzecho          #+#    #+#             */
/*   Updated: 2025/07/01 17:14:57 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

void	managing_input(t_shell_data *myshell, char *input)
{
	(void)myshell;
	if (ft_isprint(*input))
	{
		if (!isspace(*input))
			add_history(input);
	}
	myshell->head_token = input_tokenaizer(input);
	myshell->head_cmd = create_cmd_with_token(myshell);
}

static char	*extract_word(char *input, int *i)
{
	int		start;
	int		len;
	char	*result;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_metachar(input[*i])
		&& !is_quote(input[*i]))
		(*i)++;
	len = *i - start;
	result = malloc((len + 1) * sizeof(char));
	ft_strncpy(result, &input[start], len);
	result[len] = 0;
	return (result);
}

t_token	*handle_word(char *input, int *i)
{
	char	*data;
	t_token	*token;

	data = extract_word(input, i);
	if (!data)
		return (NULL);
	token = create_token(data, TOK_WORD);
	free(data);
	return (token);
}
