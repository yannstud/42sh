/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbarr_edit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 20:48:33 by slegros           #+#    #+#             */
/*   Updated: 2018/02/04 20:48:34 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dbarr_edit(char **array, char *content, int i)
{
	free(array[i]);
	array[i] = ft_strdup(content);
	return (array);
}
