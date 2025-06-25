/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:18:06 by korzecho          #+#    #+#             */
/*   Updated: 2024/03/15 17:23:35 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	compare_set(char const *s1, char const *set, int start)
{
	int	i;
	int	j;
	int	multi;

	i = start;
	j = -1;
	multi = 1;
	if (start > 0)
		multi = -1;
	while (set[++j] && (s1[i] || i + multi >= 0))
	{
		if (s1[i] == set[j])
		{
			i += multi;
			j = -1;
		}
		else if (j >= ft_strlen((char *)set))
			break ;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	finish;
	int	len;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	if (ft_strlen((char *)s1) == 0)
		return (ft_strdup(""));
	len = ft_strlen((char *)s1) - 1;
	start = compare_set(s1, set, 0);
	finish = compare_set(s1, set, len) + 1;
	return (ft_substr(s1, start, finish - start));
}
