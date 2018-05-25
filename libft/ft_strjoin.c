/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 23:01:45 by slegros           #+#    #+#             */
/*   Updated: 2017/11/12 08:38:46 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		is1;
	int		is2;
	char	*str;

	if (s1 && s2)
	{
		is1 = ft_strlen(s1);
		is2 = ft_strlen(s2);
		if (!(str = (char *)malloc((sizeof(char) * (is1 + is2)) + 1)))
			return (NULL);
		is1 = -1;
		is2 = 0;
		while (s1[++is1] != '\0')
			str[is1] = s1[is1];
		while (s2[is2] != '\0')
		{
			str[is1] = s2[is2];
			is1++;
			is2++;
		}
		str[is1] = '\0';
		return (str);
	}
	return (NULL);
}
