/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:23:05 by faikhan           #+#    #+#             */
/*   Updated: 2024/04/01 17:56:05 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	unsigned char	*ptr;
	size_t			ex;

	i = 0;
	if (start > ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	ex = ft_strlen(s) - start;
	if (len > ex)
		len = ex;
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == 0)
		return (0);
	while (s[start] != 0 && i < len)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = 0;
	return ((char *)ptr);
}
