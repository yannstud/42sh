/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_sel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swann <swann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 10:00:59 by swann             #+#    #+#             */
/*   Updated: 2018/03/05 10:01:03 by swann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		*ft_sel_create(int *select, int len)
{
	int		i;

	if (!(select = (int *)malloc(sizeof(int) * len)))
		return (NULL);
	i = -1;
	while (++i < len)
		select[i] = 0;
	return (select);
}

static int		*ft_sel_special(int len, int *select, int ed)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (ed == 97 || (ed == 114 && select[i] == 0))
			select[i] = 1;
		else if (ed == 100 || (ed == 114 && select[i] == 1))
			select[i] = 0;
		i++;
	}
	return (select);
}

int				*ft_sel(int len, int mode, int ed)
{
	static int		*select;

	if (mode == -1)
	{
		select = ft_sel_create(select, len);
		return (select);
	}
	else if (mode == -2)
		return (select);
	else if (mode == -3)
	{
		select = ft_sel_special(len, select, ed);
		return (select);
	}
	else if (mode == -4)
		free(select);
	else
	{
		if (ed == 1)
			select[mode] = (select[mode] == 1) ? 0 : 1;
		else
			select[mode] = 0;
		return (select);
	}
	return (NULL);
}
