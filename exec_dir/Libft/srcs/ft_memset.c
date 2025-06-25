/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:15:02 by korzecho          #+#    #+#             */
/*   Updated: 2024/03/01 23:01:43 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *ptr, int value, unsigned int num)
{
	unsigned char	*a;

	a = ptr;
	while (num--)
		*a++ = (unsigned char)value;
	return (ptr);
}
