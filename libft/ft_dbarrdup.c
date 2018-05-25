/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbarrdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 20:48:51 by slegros           #+#    #+#             */
/*   Updated: 2018/02/04 20:48:51 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dbarrdup(char **o_array)
{
	int		len;
	char	**n_array;
	int		i;

	i = 0;
	len = ft_dbarrlen(o_array);
	if (!(n_array = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (o_array[i] != NULL)
	{
		n_array[i] = ft_strdup(o_array[i]);
		i++;
	}
	n_array[i] = NULL;
	return (n_array);
}
