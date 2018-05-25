/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbarr_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 20:48:18 by slegros           #+#    #+#             */
/*   Updated: 2018/02/04 20:48:19 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dbarr_del(char **array, int index)
{
	char	**array2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(array2 = (char **)malloc(sizeof(char *) * ft_dbarrlen(array))))
		return (NULL);
	while (array[j] != NULL)
	{
		if (j == index && array[j + 1] == NULL)
			break ;
		if (j == index && array[j + 1] != NULL)
			j++;
		array2[i] = ft_strdup(array[j]);
		i++;
		j++;
	}
	array2[i] = NULL;
	i = -1;
	while (array[++i] != NULL)
		free(array[i]);
	free(array);
	return (array2);
}
