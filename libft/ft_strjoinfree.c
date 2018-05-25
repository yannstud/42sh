/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 19:21:52 by slegros           #+#    #+#             */
/*   Updated: 2017/12/11 22:46:06 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char const *s1, char const *s2, int mode)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (mode == 1 || mode == 3)
		free((char *)s1);
	if (mode == 2 || mode == 3)
		free((char *)s2);
	return (str);
}
