/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:19:10 by korzecho          #+#    #+#             */
/*   Updated: 2024/03/03 22:32:46 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *sml, unsigned int len)
{
	unsigned int	i;
	int				x;

	i = 0;
	if (sml == NULL || ft_strlen((char *)sml) == 0)
		return ((char *)big);
	if ((unsigned int)ft_strlen((char *)sml) > len)
		return (NULL);
	while (i < len && big[i])
	{
		x = 0;
		while (i + x < len && big[i + x] == sml[x])
		{
			x++;
			if (sml[x] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
