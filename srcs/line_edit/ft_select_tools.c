/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 09:19:12 by swann             #+#    #+#             */
/*   Updated: 2018/05/12 14:32:06 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		ft_nbelem(int len)
{
	int		*select;
	int		i;

	select = ft_sel(0, -2, 0);
	i = 0;
	while (i < len)
	{
		if (select[i] == 1)
			return (1);
		i++;
	}
	return (0);
}

static char		**ft_add_args_2(char **ar_list, int *select, int j)
{
	int		i;
	char	**res;

	res = (char **)malloc(sizeof(char *) * (j + 1));
	i = -1;
	j = 0;
	while (ar_list[++i] != NULL)
	{
		if (select[i] == 1)
		{
			res[j] = ft_strdup(ar_list[i]);
			j++;
		}
	}
	res[j] = NULL;
	return (res);
}

char			**ft_add_args(char **ar_list, int *select, int mode)
{
	int				i;
	int				j;
	static char		**res;

	if (mode == 1)
	{
		i = -1;
		j = 0;
		while (++i < ft_dbarrlen(ar_list))
		{
			if (select[i] == 1)
				j++;
		}
		res = ft_add_args_2(ar_list, select, j);
	}
	else if (mode == 2)
	{
		res = (char **)malloc(sizeof(char *) * 1);
		res[0] = NULL;
	}
	return (res);
}

static int		ft_set_pos_2(char *entry, t_grl nb, int pos, char **ar_list)
{
	if ((entry[0] == 27 || ((entry[0] == 92 || entry[0] == 127)
		&& ft_nbelem(nb.ar_len) == 0)) && entry[1] == '\0')
	{
		ft_add_args(NULL, ft_sel(nb.ar_len, -2, 0), 2);
		return (-1000);
	}
	else if (entry[0] == 10 && entry[1] == '\0')
	{
		ft_add_args(ar_list, ft_sel(nb.ar_len, -2, 0), 1);
		return (-1000);
	}
	else if ((entry[0] == 100 || entry[0] == 114 || entry[0] == 97)
		&& entry[1] == '\0')
	{
		ft_sel(nb.ar_len, -3, entry[0]);
	}
	return (pos);
}

int				ft_set_pos(char *entry, t_grl nb, int pos, char **ar_list)
{
	if (entry[0] == 27 && entry[1] == 91 && entry[2] >= 65 && entry[2] <= 68)
		pos = ft_move(nb, pos, entry);
	else if (entry[0] == 32 && entry[1] == '\0')
	{
		ft_sel(nb.ar_len, pos - 1, 1);
		pos = (pos == nb.ar_len) ? 1 : pos + 1;
	}
	else if ((entry[0] == 92 || entry[0] == 127) && ft_nbelem(nb.ar_len) != 0
		&& entry[1] == '\0')
	{
		ft_sel(nb.ar_len, pos - 1, -1);
		pos = (pos == 1) ? nb.ar_len : pos - 1;
	}
	else
		return (ft_set_pos_2(entry, nb, pos, ar_list));
	return (pos);
}
