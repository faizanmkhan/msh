/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 10:18:56 by faikhan           #+#    #+#             */
/*   Updated: 2024/04/01 15:21:10 by faikhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_length(long nbr)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		len++;
		nbr = -nbr;
	}
	else if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		num_digits;
	long	nbr;

	nbr = n;
	num_digits = number_length(n);
	ptr = malloc((num_digits + 1) * sizeof(char));
	if (nbr == 0)
		ptr[0] = 48;
	if (ptr == 0)
		return (0);
	if (nbr < 0)
	{
		ptr[0] = 45;
		nbr = -nbr;
	}
	ptr[num_digits] = 0;
	while ((num_digits - 1) >= 0 && nbr > 0)
	{
		ptr[num_digits - 1] = (nbr % 10) + 48;
		nbr = (nbr / 10);
		num_digits--;
	}
	return (ptr);
}
