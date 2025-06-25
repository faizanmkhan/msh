/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:05:20 by korzecho          #+#    #+#             */
/*   Updated: 2024/03/12 16:59:00 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

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
