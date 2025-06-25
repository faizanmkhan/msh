/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:22:12 by faikhan           #+#    #+#             */
/*   Updated: 2024/03/31 20:22:14 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	od;

	i = 0;
	while (dst[i] && i < size)
		i++;
	od = i;
	j = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (size && i < size - 1)
	{
		while (src[j] != 0 && i < size - 1)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
	}
	if (od < size)
		dst[i] = '\0';
	return (od + ft_strlen(src));
}
