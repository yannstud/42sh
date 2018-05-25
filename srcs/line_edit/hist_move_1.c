/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_move_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 07:13:35 by slegros           #+#    #+#             */
/*   Updated: 2018/05/15 16:38:14 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_hist_supermove_left(t_h *the)
{
	if (the->j != 0)
	{
		while (ft_isspace(the->hist[the->i][the->j - 1]) == 1 && the->j != 0)
		{
			ft_hist_move_left(the, 0);
			the->j--;
		}
		while (the->j != 0 && ft_isspace(the->hist[the->i][the->j - 1]) == 0)
		{
			ft_hist_move_left(the, 0);
			the->j--;
		}
	}
	else
		ft_putstr_fd(tgetstr("bl", NULL), 0);
}

static void		ft_hist_supermove_right(t_h *the, int move, int len)
{
	if (move < 0)
	{
		if (the->j != len)
		{
			while (ft_isspace(the->hist[the->i][the->j]) == 0 && the->j != len)
			{
				the->j++;
				ft_hist_move_right(the, 0);
			}
			while (ft_isspace(the->hist[the->i][the->j]) == 1 && the->j != len)
			{
				the->j++;
				ft_hist_move_right(the, 0);
			}
		}
		else
			ft_putstr_fd(tgetstr("bl", NULL), 0);
	}
	else
		ft_hist_supermove_left(the);
}

void			ft_hist_supermove(t_h *the, int mode, int move)
{
	if (mode == 11)
	{
		if (move > 0 && the->j != 0)
		{
			while (the->j > 0)
			{
				the->j--;
				ft_hist_move_left(the, 1);
			}
		}
		else if (move < 0 && the->j != (int)ft_strlen(the->hist[the->i]))
		{
			while (the->j < (int)ft_strlen(the->hist[the->i]))
			{
				the->j++;
				ft_hist_move_right(the, 0);
			}
		}
		else
			ft_putstr_fd(tgetstr("bl", NULL), 0);
	}
	else if (mode == 12)
		ft_hist_supermove_right(the, move, (int)ft_strlen(the->hist[the->i]));
	else
		ft_hist_jump(the, move, ft_get_winsize(0));
}

void			ft_hist_move_left(t_h *the, int val)
{
	t_wsize		w;

	w = ft_get_winsize(0);
	if ((the->j + val + ft_strlen(ft_where(0, NULL))) % w.ws_col == 0)
	{
		ft_putstr_fd(tgoto(tgetstr("ch", NULL), 0, w.ws_col - 1), 0);
		ft_putstr_fd(tgetstr("up", NULL), 0);
	}
	else
		ft_putstr_fd(tgetstr("le", NULL), 0);
}

void			ft_hist_move_right(t_h *the, int val)
{
	t_wsize		w;

	w = ft_get_winsize(0);
	if ((the->j + val + ft_strlen(ft_where(0, NULL))) % w.ws_col == 0)
	{
		ft_putstr_fd(tgetstr("cr", NULL), 0);
		ft_putstr_fd(tgetstr("do", NULL), 0);
	}
	else
		ft_putstr_fd(tgetstr("nd", NULL), 0);
}
