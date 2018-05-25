/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 23:21:26 by slegros           #+#    #+#             */
/*   Updated: 2017/11/10 22:26:44 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	size_t	j;

	if (ft_strlen(str2) == 0)
		return ((char *)str1);
	i = 0;
	while (str1[i] != '\0' && i < n)
	{
		j = 0;
		while (str1[i + j] == str2[j] && (i + j) < n && str1[i + j] != '\0')
		{
			if (str2[j + 1] == '\0')
				return ((char *)&str1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
