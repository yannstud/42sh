/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 05:49:09 by slegros           #+#    #+#             */
/*   Updated: 2017/11/12 08:34:55 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	size;
	char			*str;

	if (s)
	{
		size = ft_strlen((char *)s);
		if (!(str = (char *)malloc((sizeof(char) * size) + 1)))
			return (NULL);
		i = 0;
		while (s[i] != '\0')
		{
			str[i] = f(i, (char)(s[i]));
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
