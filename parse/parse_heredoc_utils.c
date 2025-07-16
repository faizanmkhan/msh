/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:21:53 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

char	*find_delimiter(char *str, bool *has_quotes)
{
	int	i;

	i = ft_strlen(str);
	if ((str[0] == '\'' && str[i - 1] == '\'')
		|| (str[0] == '\"' && str[i - 1] == '\"'))
	{
		*has_quotes = true;
		return (ft_strtrim(str, "\'\""));
	}
	return (ft_strdup(str));
}

char	*heredoc_filename(void)
{
	static int	index;
	char		*file_name;
	char		*index_str;

	index_str = ft_itoa(index);
	if (!index_str)
		return (NULL);
	++index;
	file_name = ft_strjoin(HEREDOC_FILENAME, index_str);
	free(index_str);
	return (file_name);
}

static size_t	calculate_total_length(char **tab)
{
	size_t	total_len;
	int		i;

	total_len = 0;
	i = 0;
	while (tab[i])
	{
		total_len += ft_strlen(tab[i]);
		if (tab[i + 1])
			total_len++;
		i++;
	}
	return (total_len);
}

static void	copy_strings(char *str, char **tab)
{
	size_t	pos;
	int		i;
	size_t	len;

	pos = 0;
	i = 0;
	while (tab[i])
	{
		len = ft_strlen(tab[i]);
		ft_strlcpy(str + pos, tab[i], len + 1);
		pos += len;
		if (tab[i + 1])
		{
			str[pos] = ' ';
			pos++;
		}
		i++;
	}
	str[pos] = '\0';
}

char	*join_words_with_spaces(char **tab)
{
	char	*str;
	size_t	total_len;

	total_len = calculate_total_length(tab);
	str = malloc(total_len + 1);
	if (!str)
	{
		free_str_tab(tab);
		return (NULL);
	}
	copy_strings(str, tab);
	free_str_tab(tab);
	return (str);
}
