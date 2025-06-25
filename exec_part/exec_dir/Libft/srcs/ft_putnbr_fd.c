/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:20:13 by korzecho          #+#    #+#             */
/*   Updated: 2024/03/22 13:20:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	char	c[10];
	short	i;

	nbr = n;
	i = 0;
	if (n == 0)
	{
		write (fd, "0", 1);
		return ;
	}
	if (nbr < 0)
	{
		nbr *= -1;
		write (fd, "-", 1);
	}
	while (nbr)
	{
		c[i++] = (nbr % 10) + 48;
		nbr /= 10;
	}
	while (i > 0)
		write(fd, &c[--i], 1);
}
