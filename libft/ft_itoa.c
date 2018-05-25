/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 02:34:31 by slegros           #+#    #+#             */
/*   Updated: 2017/11/12 04:34:37 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int					neg;
	unsigned int		nb;
	int					size;
	char				*str;

	neg = 0;
	size = 0;
	if (n < 0)
	{
		neg = 1;
		size++;
		n *= (-1);
	}
	nb = n;
	while (n /= 10)
		size++;
	if (!(str = (char *)malloc(sizeof(char) * size + 2)))
		return (NULL);
	str[size + 1] = '\0';
	str[size] = (nb % 10) + 48;
	while (nb /= 10)
		str[--size] = (nb % 10) + 48;
	if (neg == 1)
		str[--size] = '-';
	return (str);
}
