/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 18:33:17 by slegros           #+#    #+#             */
/*   Updated: 2018/05/22 15:58:49 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		ft_get_word_2(char *str, int *mode, int j)
{
	if (str[j] != '\0' && str[j] == '!')
	{
		*mode = 1;
		return (1);
	}
	if (str[j] != '\0' && str[j] == '#')
	{
		*mode = 6;
		return (1);
	}
	return (0);
}

static int		ft_get_word(char *str, int start, int *mode)
{
	int		j;

	j = start + 1;
	if (ft_get_word_2(str, mode, j) == 1)
		return (j + 1);
	if (str[j] != '\0' && str[j] == '?')
		*mode = 2;
	while (str[j] != '\0' && str[j] != ' ' && str[j] != '\t' && str[j] != '='
		&& str[j] != '(')
	{
		j++;
		if (str[j - 1] == '?' && (j - 1) > start + 1 && *mode == 2)
			break ;
	}
	if (j > start + 1)
	{
		if (ft_isdigit(str[start + 1]) == 1)
			*mode = 3;
		if (j > start + 2 && str[start + 1] == '-'
			&& ft_isdigit(str[start + 2]) == 1)
			*mode = 4;
		if (*mode == 2 && j > start + 2 && str[j - 1] == '?')
			*mode = 5;
	}
	return (j);
}

static char		*ft_geteventname(char *str, int start, int *j, int mode)
{
	char	*tmp;

	tmp = NULL;
	if (mode == 3 || mode == 4)
	{
		*j = (mode == 3) ? start + 1 : start + 2;
		while (str[*j] != '\0' && ft_isdigit(str[*j]) == 1)
			*j = *j + 1;
		tmp = ft_strsub(str, start + 1, *j - (start + 1));
	}
	else if (mode == 2 || mode == 5)
	{
		if (*j > start + 1)
			tmp = ft_strsub(str, start + 2, *j - (start + 2));
		if (mode == 5)
			tmp = ft_strsubf(tmp, 0, ft_strlen(tmp) - 1);
	}
	else
		tmp = ft_strsub(str, start + 1, *j - (start + 1));
	return (tmp);
}

static char		*ft_exclam_str(char *str, int start, int *ok)
{
	int		j;
	int		mode;
	char	*tmp;
	char	*evt;

	mode = 0;
	j = ft_get_word(str, start, &mode);
	if (j - start > 1)
	{
		if ((tmp = ft_geteventname(str, start, &j, mode)) != NULL)
		{
			if ((evt = ft_getevent(tmp, mode, start, str)) != NULL)
			{
				str = ft_excla_replace(str, evt, start, j);
				*ok = 1;
				free(evt);
			}
			else
				return (ft_exclam_error(tmp, str, mode));
			free(tmp);
		}
	}
	return (str);
}

char			*ft_exclamation(char *str)
{
	int		i;
	int		ok;

	ft_sigupk(1, 1);
	i = -1;
	ok = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '!' && ft_inbrk(str, i) == 0)
			str = ft_exclam_str(str, i, &ok);
		if (i >= (int)ft_strlen(str))
			break ;
	}
	if (ok == 1)
	{
		ft_history(21, str, 0);
		ft_putendl_fd(str, 0);
	}
	ft_sigupk(1, 0);
	return (str);
}
