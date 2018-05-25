/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_move_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:13:46 by slegros           #+#    #+#             */
/*   Updated: 2018/05/10 15:59:09 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_hist_up_down_2(t_h *the, t_wsize w)
{
	ft_putstr_fd(tgetstr("cr", NULL), 0);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	ft_putstr_col_fd(ft_where(0, NULL), BOLD, 0);
	ft_putstr_fd(the->hist[the->i], 0);
	if ((the->j + ft_strlen(ft_where(0, NULL))) % w.ws_col == 0)
	{
		ft_putstr_fd(tgetstr("cr", NULL), 0);
		ft_putstr_fd(tgetstr("do", NULL), 0);
	}
}

static void		ft_hist_up_down(t_h *the, int move)
{
	t_wsize		w;
	int			j_line;

	if ((move < 0 && the->i != 0)
		|| (move > 0 && the->i != (ft_dbarrlen(the->hist) - 1)))
	{
		w = ft_get_winsize(0);
		j_line = (the->j + ft_strlen(ft_where(0, NULL))) / w.ws_col;
		the->i += move;
		if (the->i == ft_dbarrlen(the->hist) - 2
			&& ft_button_line(0, 0) == 2)
			the->i += move;
		the->j = ft_strlen(the->hist[the->i]);
		ft_putstr_fd(tgetstr("dl", NULL), 0);
		while (j_line > 0)
		{
			ft_putstr_fd(tgetstr("up", NULL), 0);
			j_line--;
		}
		ft_hist_up_down_2(the, w);
	}
	else
		ft_putstr_fd(tgetstr("bl", NULL), 0);
}

static void		ft_hist_left_right(int len, t_h *the, int move)
{
	t_wsize		w;

	if ((move < 0 && the->j != len) || (move > 0 && the->j != 0))
	{
		w = ft_get_winsize(0);
		if (move < 0)
			ft_hist_move_right(the, 1);
		else
			ft_hist_move_left(the, 0);
		the->j += (move * -1);
	}
	else
		ft_putstr_fd(tgetstr("bl", NULL), 0);
}

void			ft_hist_move(t_h *the, int modove)
{
	int		move;
	int		mode;

	if (modove > 0)
	{
		move = 1;
		mode = modove;
	}
	else
	{
		move = -1;
		mode = modove * -1;
	}
	if (mode == 4)
		ft_hist_up_down(the, move);
	else
		ft_hist_left_right((int)ft_strlen(the->hist[the->i]), the, move);
}
