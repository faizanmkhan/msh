/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 20:20:42 by faikhan           #+#    #+#             */
/*   Updated: 2024/03/31 20:20:44 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*temp_dest;
	const unsigned char	*temp_src;

	temp_dest = dest;
	temp_src = src;
	if (src < dest)
	{
		temp_dest += n;
		temp_src += n;
		while (n--)
		{
			*--temp_dest = *--temp_src;
		}
	}
	else
	{
		while (n--)
		{
			*temp_dest++ = *temp_src++;
		}
	}
	return (dest);
}
