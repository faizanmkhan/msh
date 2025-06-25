/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 01:46:28 by faikhan           #+#    #+#             */
/*   Updated: 2024/04/01 13:43:52 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != 0 && s[i] != c)
				i++;
		}
		else if (s[i] == c)
			i++;
	}
	return (count);
}

size_t	word_length(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != 0 && s[i] != c)
		i++;
	return (i);
}

static void	free_array(size_t i, char **array)
{
	while (i > 0)
	{
		i--;
		free(&array[i]);
	}
	free(array);
}

static char	**split_word(char const *s, char c, char **array, size_t word_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < word_count)
	{
		while (s[j] && s[j] == c)
			j++;
		array[i] = ft_substr(s, j, word_length(&s[j], c));
		if (!array[i])
		{
			free_array(i, array);
			return (0);
		}
		while (s[j] && s[j] != c)
			j++;
		i++;
	}
	array[i] = 0;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	words;

	if (!s)
		return (0);
	words = count_word(s, c);
	array = (char **)malloc((words + 1) * (sizeof(char *)));
	if (!array)
		return (0);
	array = split_word(s, c, array, words);
	return (array);
}
