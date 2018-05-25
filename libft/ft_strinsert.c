/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:00:59 by slegros           #+#    #+#             */
/*   Updated: 2018/02/17 06:21:18 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strinsert(char *s1, char c, int place)
{
	char	*s2;
	int		i;
	int		j;

	s2 = ft_strnew(ft_strlen(s1) + 1);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		if (j == place)
			j++;
		s2[j] = s1[i];
		j++;
		i++;
	}
	s2[place] = c;
	free(s1);
	return (s2);
}
