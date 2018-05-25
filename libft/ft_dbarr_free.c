/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbarr_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 12:09:02 by slegros           #+#    #+#             */
/*   Updated: 2018/04/21 18:09:20 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dbarr_free(char **array)
{
	int		i;

	i = -1;
	while (array[++i] != NULL)
		free(array[i]);
	free(array);
	return (array);
}
