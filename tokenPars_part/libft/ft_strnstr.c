/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:22:45 by faikhan           #+#    #+#             */
/*   Updated: 2024/04/01 17:13:31 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == 0)
		return ((char *) haystack);
	while (haystack[i] != 0 && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			j++;
			if (needle[j] == 0)
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}

// char	*ft_strnstr(const char *s, const char *to_find, size_t n)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	if (to_find[0] == 0)
// 		return ((char *)s);
// 	else if (n == 0)
// 		return (0);
// 	while (s[i] != 0 && i < n)
// 	{
// 		j = 0;
// 		while (to_find[j] != 0 && s[i + j] == to_find[j])
// 		{
// 			j++;
// 			if (to_find[j] == 0)
// 				return ((char *)&s[i]);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
