/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:34:57 by korzecho          #+#    #+#             */
/*   Updated: 2024/09/08 14:34:58 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*ptr;

	i = 0;
	if (!s)
		return (ft_strdup(""));
	if (start > (unsigned int)ft_strlen((char *)s))
		return (ft_strdup(""));
	if (len > (unsigned int)ft_strlen((char *)s + start))
		len = ft_strlen((char *)s + start);
	ptr = malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (ft_strdup(""));
	while (s[i] && i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strlen(char *arg)
{
	int	i;

	i = 0;
	while (*arg)
	{
		if (*arg++ != '\0')
			i++;
	}
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*dst;
	int		len;
	char	*start;

	if (!str)
		return (NULL);
	len = ft_strlen((char *)str);
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	start = dst;
	while (*str)
	{
		*dst++ = *str++;
	}
	*dst = '\0';
	return (start);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*ptr;

	j = 0;
	if (!s1 && !s2)
		return ("");
	i = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ptr = (char *)malloc(i * sizeof(char) + 1);
	if (!ptr)
		return (NULL);
	while (*s1)
		ptr[j++] = *s1++;
	while (*s2)
		ptr[j++] = *s2++;
	ptr[j] = '\0';
	return (ptr);
}
