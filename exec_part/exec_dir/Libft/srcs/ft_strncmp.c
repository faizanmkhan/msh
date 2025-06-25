/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:06:05 by korzecho          #+#    #+#             */
/*   Updated: 2024/03/03 20:37:36 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp( const char *str1, const char *str2, unsigned int n)
{
	unsigned int	i;
	int				result;

	i = 0;
	if (n == 0)
		return (0);
	else
		n -= 1;
	while (i < n && (str1[i] || str2[i]) && str1[i] == str2[i])
		i++;
	result = 1;
	if (str1[i] < 0 || str2[i] < 0)
		result = -1;
	else if (str1[i] < 0 && str2[i] < 0)
		result = 1;
	if (str1[i] == str2[i])
		result = 0;
	return ((str1[i] - str2[i]) * result);
}
