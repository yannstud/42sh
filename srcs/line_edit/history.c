/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 11:34:41 by slegros           #+#    #+#             */
/*   Updated: 2018/05/23 14:05:10 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_put_history(t_h the)
{
	ft_putstr_fd(tgetstr("cl", NULL), 0);
	ft_putstr_col_fd(ft_where(0, NULL), BOLD, 0);
	ft_putstr_fd(the.hist[the.i], 0);
}

static void		ft_history_2(t_h *the, int mode, int move)
{
	if (mode == 4 || mode == 7)
		ft_hist_move(the, move * mode);
	else if (mode == 11 || mode == 12 || mode == 16)
		ft_hist_supermove(the, mode, move);
	else if (mode == 26)
		the->start = move;
}

static void		ft_history_eof(t_h *the)
{
	free(the->hist[the->i]);
}

t_h				ft_history(int mode, char *buf, int move)
{
	static char		**save_hist;
	static t_h		the;

	if (mode == 1 || mode == 19 || mode == 24)
		ft_hist_init(&the, mode);
	else if (mode == 2)
		save_hist = ft_hist_init(&the, mode);
	else if (mode == 3 || mode == 8 || mode == 9 || mode == 20 || mode == 21
		|| mode == 27)
		ft_hist_edit(&the, buf, mode);
	else if (mode == 5 || mode == 6 || mode == 13)
		ft_hist_enter(&the, save_hist, mode);
	else if (mode == 14 || mode == 15)
		mode == 14 ? ft_put_history(the) : ft_hist_upk(&the, move);
	else if (mode == 17 || mode == 18)
		mode == 17 ? ft_hist_eot(&the, move) : ft_hist_tab(&the);
	else if (mode == 22)
		the.hist = ft_dbarr_del(the.hist, move);
	else if (mode == 23)
		ft_hist_merge(&the);
	else if (mode == 25)
		ft_history_eof(&the);
	else
		ft_history_2(&the, mode, move);
	return (the);
}
