/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:06:13 by slegros           #+#    #+#             */
/*   Updated: 2018/02/19 08:20:17 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrem(char *s1, int place)
{
	char	*s2;
	int		i;
	int		j;

	s2 = ft_strnew(ft_strlen(s1) - 1);
	if (place == (int)(ft_strlen(s1) - 1))
	{
		s2 = ft_strncpy(s2, s1, ft_strlen(s1) - 1);
		free(s1);
		return (s2);
	}
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		if (j == place)
			i++;
		s2[j] = s1[i];
		j++;
		i++;
	}
	free(s1);
	return (s2);
}
