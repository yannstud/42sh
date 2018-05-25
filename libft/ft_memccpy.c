/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 22:41:44 by slegros           #+#    #+#             */
/*   Updated: 2017/11/12 09:39:55 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	char	*dstc;
	char	*srcc;

	i = 0;
	dstc = (char *)dst;
	srcc = (char *)src;
	while (i < n)
	{
		dstc[i] = srcc[i];
		if (dstc[i] == (char)c)
			return (&dstc[i + 1]);
		i++;
	}
	return (NULL);
}
