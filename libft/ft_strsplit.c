/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 01:01:17 by slegros           #+#    #+#             */
/*   Updated: 2018/03/27 14:40:00 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbwd(char *s, char c)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			nb++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (nb);
}

static int	ft_wdsz(char *s, int k, char c)
{
	int		i;

	i = 0;
	while (s[k] != c && s[k] != '\0')
	{
		i++;
		k++;
	}
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	int		size;
	char	**res;

	i = -1;
	k = 0;
	if (s == NULL ||
		!(res = (char **)malloc(sizeof(char *) * (ft_nbwd((char *)s, c) + 1))))
		return (NULL);
	while (++i < ft_nbwd((char *)s, c))
	{
		j = -1;
		while (s[k] == c && s[k] != '\0')
			k++;
		size = ft_wdsz((char *)s, k, c);
		if (!(res[i] = (char *)malloc(sizeof(char) * (size + 1))))
			return (NULL);
		while (++j < size && s[k] != '\0')
			res[i][j] = (char)s[k++];
		res[i][j] = '\0';
	}
	res[i] = NULL;
	return (res);
}
