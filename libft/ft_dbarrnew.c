/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbarrnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 11:34:43 by slegros           #+#    #+#             */
/*   Updated: 2018/04/10 19:59:13 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dbarrnew(int nb)
{
	char	**dbarr;
	int		i;

	if (!(dbarr = (char **)malloc(sizeof(char *) * (nb + 1))))
		return (NULL);
	i = 0;
	while (i < nb + 1)
	{
		dbarr[i] = NULL;
		i++;
	}
	return (dbarr);
}
