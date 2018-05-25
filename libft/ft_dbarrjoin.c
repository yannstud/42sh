/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbarrjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 01:10:37 by slegros           #+#    #+#             */
/*   Updated: 2018/03/02 01:17:03 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dbarrjoin(char **dbarr1, char **dbarr2)
{
	int		l1;
	int		l2;
	char	**dbarr;
	int		i;

	l1 = ft_dbarrlen(dbarr1);
	l2 = ft_dbarrlen(dbarr2);
	if (!(dbarr = (char **)malloc(sizeof(char *) * (l1 + l2 + 1))))
		return (NULL);
	i = 0;
	while (dbarr1[i] != NULL)
	{
		dbarr[i] = ft_strdup(dbarr1[i]);
		i++;
	}
	i = 0;
	while (dbarr2[i] != NULL)
	{
		dbarr[i + l1] = ft_strdup(dbarr2[i]);
		i++;
	}
	dbarr[i + l1] = NULL;
	return (dbarr);
}
