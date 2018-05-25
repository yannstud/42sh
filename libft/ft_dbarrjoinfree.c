/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbarrjoinfree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 01:21:01 by slegros           #+#    #+#             */
/*   Updated: 2018/03/02 01:21:23 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dbarrjoinfree(char **dbarr1, char **dbarr2, int mode)
{
	char	**dbarr;

	dbarr = ft_dbarrjoin(dbarr1, dbarr2);
	if (mode == 1 || mode == 3)
		ft_dbarr_free(dbarr1);
	if (mode == 2 || mode == 3)
		ft_dbarr_free(dbarr2);
	return (dbarr);
}
