/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:47:38 by slegros           #+#    #+#             */
/*   Updated: 2017/11/10 06:09:59 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str1, const char *str2)
{
	int	i;
	int	j;

	if (ft_strlen(str2) == 0)
		return ((char *)str1);
	i = 0;
	while (str1[i] != '\0')
	{
		j = 0;
		while (str1[i + j] == str2[j])
		{
			if (str2[j + 1] == '\0')
				return ((char *)&str1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
