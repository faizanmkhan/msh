/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:10:40 by korzecho          #+#    #+#             */
/*   Updated: 2024/03/22 15:10:41 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	if (nmemb <= 0 && size <= 0)
		return (ft_strdup(""));
	if (nmemb >= SIZE_MAX || size >= SIZE_MAX || nmemb * size >= SIZE_MAX)
		return (NULL);
	result = malloc(size * nmemb);
	if (!result)
		return (NULL);
	ft_bzero(result, (nmemb * size));
	return (result);
}
