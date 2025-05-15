/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:10:16 by korzecho          #+#    #+#             */
/*   Updated: 2024/03/21 13:10:18 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	int_size(long l)
{
	int		size;

	size = 0;
	if (l < 0)
		l *= -1;
	while (l)
	{
		l /= 10;
		size++;
	}
	return (size);
}

static char	*reverse_string(char *str, int size)
{
	int		f;
	int		j;
	char	c;

	f = 0;
	j = size - 1;
	while (f <= j)
	{
		c = str[f];
		str[f] = str[j];
		str[j] = c;
		f++;
		j--;
	}
	str[size] = '\0';
	return (str);
}

static char	*convert(char *str, long p, int size)
{
	int		i;
	int		bool;
	char	c;

	bool = 0;
	i = 0;
	if (p < 0)
	{
		bool = 1;
		p *= -1;
	}
	while (i < size)
	{
		c = p % 10 + '0';
		p /= 10;
		if (c >= '0' && c <= '9')
			str[i] = c;
		else if (str[i] == '-')
			str[i] = '-';
		i++;
	}
	if (bool)
		str[i - 1] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*x;
	long	p;
	int		size;

	if (n == 0)
	{
		x = (char *)malloc(sizeof(char) + 1);
		if (!x)
			return (NULL);
		x[0] = '0';
		x[1] = '\0';
		return (x);
	}
	p = n;
	size = 0;
	size = int_size(p);
	if (p < 0)
		size++;
	x = (char *)malloc(size + 1);
	if (!x)
		return (NULL);
	p = n;
	x = convert(x, p, size);
	return (reverse_string(x, size));
}
