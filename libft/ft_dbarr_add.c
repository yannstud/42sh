/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbarr_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 20:48:07 by slegros           #+#    #+#             */
/*   Updated: 2018/02/04 20:48:10 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dbarr_add(char **array, char *content)
{
	int		len;
	char	**array2;
	int		i;

	i = 0;
	len = ft_dbarrlen(array) + 1;
	if (!(array2 = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (array[i] != NULL)
	{
		array2[i] = ft_strdup(array[i]);
		i++;
	}
	array2[i] = ft_strdup(content);
	i++;
	array2[i] = NULL;
	i = -1;
	while (array[++i] != NULL)
		free(array[i]);
	free(array);
	return (array2);
}
