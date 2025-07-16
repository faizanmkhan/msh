/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:19:10 by faikhan           #+#    #+#             */
/*   Updated: 2024/04/01 18:05:09 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*ptr;

	if (nmemb > 0 && (2147483647 / nmemb) < size)
	{
		return (0);
	}
	i = nmemb * size;
	ptr = malloc(i);
	if (ptr == 0)
		return (0);
	if (size == 0 || nmemb == 0)
	{
		size = 1;
		nmemb = 1;
	}
	if (size + nmemb > 2147483647)
		return (0);
	while (i > 0)
	{
		ptr[i - 1] = 0;
		i--;
	}
	return ((void *)ptr);
}
