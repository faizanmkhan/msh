/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:59:24 by korzecho          #+#    #+#             */
/*   Updated: 2025/07/16 13:59:25 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/myshell.h"

static int	check_blank(char *str)
{
	int	i;
	int	space;

	i = 0;
	space = 1;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			space = 0;
		else
		{
			space = 1;
			return (space);
		}
		i++;
	}
	return (space);
}

void	managing_input(t_shell_data *myshell, char *input)
{
	(void)myshell;
	if (ft_isprint(*input))
	{
		if (check_blank(input))
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
