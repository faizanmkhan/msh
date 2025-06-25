/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:54:01 by korzecho          #+#    #+#             */
/*   Updated: 2024/03/03 21:08:20 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, unsigned int n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	unsigned int	i;

	ptr1 = (unsigned char *)str1;
	ptr2 = (unsigned char *)str2;
	i = 0;
	if (n <= 0 || !str1 || !str2)
		return (0);
	n -= 1;
	while (i < n && (ptr1[i] || ptr2[i]) && ptr1[i] == ptr2[i])
		i++;
	if (ptr1[i] == ptr2[i])
		return (0);
	else
		return (ptr1[i] - ptr2[i]);
}
