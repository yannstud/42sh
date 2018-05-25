/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_enter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 18:21:25 by slegros           #+#    #+#             */
/*   Updated: 2018/05/20 17:34:29 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_hist_enter_2(t_h *the, char **save_hist)
{
	int		len;

	len = ft_dbarrlen(the->hist) - 1;
	if (the->i != len)
	{
		free(the->hist[len]);
		the->hist[len] = ft_strdup(the->hist[the->i]);
	}
	the->hist = ft_hist_restore(the->hist, save_hist);
	save_hist = ft_dbarr_free(save_hist);
}

static void		ft_hist_enter_3(t_h *the, int mode)
{
	ft_button_line(1, 3);
	ft_where(2, NULL);
	ft_where(1, NULL);
	if (mode != 1)
		the->hist = ft_dbarr_del(the->hist, ft_dbarrlen(the->hist) - 1);
}

void			ft_hist_enter(t_h *the, char **save_hist, int mode)
{
	if (mode == 5)
		ft_hist_enter_2(the, save_hist);
	else if (mode == 13)
	{
		the->hist = ft_hist_restore(the->hist, save_hist);
		if (ft_button_line(0, 0) == 4)
			ft_hist_enter_3(the, 1);
		else
		{
			if (ft_button_line(0, 0) == 2)
				ft_hist_enter_3(the, 2);
			free(the->hist[ft_dbarrlen(the->hist) - 1]);
			the->hist[ft_dbarrlen(the->hist) - 1] = ft_strnew(0);
		}
		the->i = ft_dbarrlen(the->hist) - 1;
		the->j = 0;
	}
	else
		the->hist = ft_dbarr_free(the->hist);
}
