/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 19:29:39 by slegros           #+#    #+#             */
/*   Updated: 2017/12/11 19:41:14 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsubf(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	if (s)
	{
		i = 0;
		if (!(str = (char *)malloc((sizeof(char) * len) + 1)))
			return (NULL);
		while (len > 0)
		{
			str[i] = s[start + i];
			i++;
			len--;
		}
		str[i] = '\0';
		ft_strdel((char **)&s);
		return (str);
	}
	return (NULL);
}
