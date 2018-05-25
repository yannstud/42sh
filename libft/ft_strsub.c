/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 22:44:28 by slegros           #+#    #+#             */
/*   Updated: 2017/11/12 08:34:18 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	if (s)
	{
		i = 0;
		if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		while (len > 0)
		{
			str[i] = s[start + i];
			i++;
			len--;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
