/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 23:10:55 by slegros           #+#    #+#             */
/*   Updated: 2017/11/14 00:29:35 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	unsigned int	i;
	unsigned int	j;

	if (s)
	{
		i = 0;
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		if (s[i] == '\0')
			return (ft_strnew(0));
		j = i;
		while (s[j] != '\0')
			j++;
		while (s[j - 1] == ' ' || s[j - 1] == '\t' || s[j - 1] == '\n')
			j--;
		j--;
		return (ft_strsub(s, i, (j - i) + 1));
	}
	return (NULL);
}
