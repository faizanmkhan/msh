/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:13:49 by korzecho          #+#    #+#             */
/*   Updated: 2024/03/13 21:13:50 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

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
