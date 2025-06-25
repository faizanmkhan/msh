/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:44:56 by korzecho          #+#    #+#             */
/*   Updated: 2024/03/03 20:00:56 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	len;

	len = ft_strlen((char *)str);
	while (len >= 0)
	{
		if (str[len] == (char)c)
			return ((char *)str + len);
		len--;
	}
	return (NULL);
}
