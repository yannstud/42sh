/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stristr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 14:50:36 by slegros           #+#    #+#             */
/*   Updated: 2018/05/22 16:25:20 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stristr(char *str1, char *str2)
{
	int		i;
	int		j;

	if (ft_strlen(str2) == 0)
		return (0);
	i = 0;
	while (str1[i] != '\0')
	{
		j = 0;
		while (str1[i + j] == str2[j])
		{
			if (str2[j + 1] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}
