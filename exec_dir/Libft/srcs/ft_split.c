/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:20:07 by korzecho          #+#    #+#             */
/*   Updated: 2024/03/27 14:20:09 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	i;

	i = 0;
	if (!*s || !s)
		return (0);
	else if (*s++ != c)
		i++;
	while (*s)
	{
		if (*s++ == c && (*s >= 32 && *s <= 126) && *s != c)
			i++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static char	**mem_clear(char **split, int i)
{
	if (!split[i])
	{
		while (i >= 0)
			free(split[i--]);
		free(split);
		return (NULL);
	}
	return (split);
}

static char	**terminate(char **split, int i)
{
	split[i] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		index;
	char	**result;

	result = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	j = 0;
	i = -1;
	index = -1;
	while (++i <= ft_strlen((char *)s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen((char *)s)) && index >= 0)
		{
			result[j] = word_dup(s, index, i);
			if (result[j++])
				mem_clear(result, j - 1);
			index = -1;
		}
	}
	return (terminate(result, j));
}
