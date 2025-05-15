/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:56:22 by korzecho          #+#    #+#             */
/*   Updated: 2024/03/03 13:36:06 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*ptr;
	char	sign;

	sign = c;
	ptr = (char *)str;
	while (*ptr != sign && *ptr)
		ptr++;
	if (*ptr == sign)
		return (ptr);
	return (NULL);
}
