/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:42:22 by korzecho          #+#    #+#             */
/*   Updated: 2024/03/22 20:42:24 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dst;
	int		len;
	char	*start;

	if (!str)
		return (NULL);
	len = ft_strlen((char *)str);
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	start = dst;
	while (*str)
	{
		*dst++ = *str++;
	}
	*dst = '\0';
	return (start);
}
