/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 16:07:56 by slegros           #+#    #+#             */
/*   Updated: 2018/05/22 17:06:43 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			*ft_getevent(char *name, int mode, int start, char *str)
{
	char	*evt;

	evt = NULL;
	if (mode == 1)
		evt = ft_exclamsearchint("-1");
	if (mode == 3 || mode == 4)
		evt = ft_exclamsearchint(name);
	if (mode == 0 || mode == 2 || mode == 5)
		evt = ft_exclamsearchchar(name, mode);
	if (mode == 6)
		evt = ft_strsub(str, 0, start);
	return (evt);
}

char			*ft_exclamsearchint(char *tmp)
{
	int		index;
	t_h		the;
	char	*res;
	int		i;

	index = ft_atoi(tmp);
	the = ft_history(0, NULL, 0);
	if (ft_toabs(index) >= ft_dbarrlen(the.hist) || index == 0)
		return (NULL);
	if (index > 0)
		res = ft_strdup(the.hist[index - 1]);
	else
	{
		i = ft_dbarrlen(the.hist) - 1;
		index--;
		while (++index < 0)
			i--;
		res = ft_strdup(the.hist[i]);
	}
	return (res);
}

static int		ft_exclamsearch_mode2(char *str1, char *str2)
{
	int		i;
	int		j;

	if (ft_strlen(str2) == 0)
		return (1);
	if (ft_strlen(str2) > ft_strlen(str1))
		return (0);
	i = ft_strlen(str1) - ft_strlen(str2);
	j = 0;
	while (str1[i] != '\0')
	{
		if (str1[i] != str2[j])
			return (0);
		i++;
		j++;
	}
	return (1);
}

char			*ft_exclamsearchchar(char *tmp, int mode)
{
	t_h		the;
	int		i;
	char	*res;

	the = ft_history(0, NULL, 0);
	i = ft_dbarrlen(the.hist) - 2;
	res = NULL;
	while (i >= 0)
	{
		if (mode == 0 && ft_strncmp(tmp, the.hist[i], ft_strlen(tmp)) == 0)
			return ((res = ft_strdup(the.hist[i])));
		if (mode == 2 && ft_exclamsearch_mode2(the.hist[i], tmp) == 1)
			return ((res = ft_strdup(the.hist[i])));
		if (mode == 5 && ft_strstr(the.hist[i], tmp) != NULL)
			return ((res = ft_strdup(the.hist[i])));
		i--;
	}
	return (NULL);
}
