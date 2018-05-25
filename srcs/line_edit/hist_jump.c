/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_jump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 02:51:36 by slegros           #+#    #+#             */
/*   Updated: 2018/04/30 17:27:49 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		ft_hist_jump_2(int move, t_wsize w, t_h *the)
{
	while (move < the->j && move < (int)ft_strlen(the->hist[the->i]))
	{
		move++;
		if ((move + ft_strlen(ft_where(0, NULL))) % w.ws_col == 0)
		{
			ft_putstr_fd(tgetstr("cr", NULL), 0);
			ft_putstr_fd(tgetstr("do", NULL), 0);
		}
		else
			ft_putstr_fd(tgetstr("nd", NULL), 0);
	}
	return (move);
}

void			ft_hist_jump(t_h *the, int move, t_wsize w)
{
	int		j_line;
	int		n_line;

	j_line = (the->j + ft_strlen(ft_where(0, NULL))) / w.ws_col;
	n_line = (ft_strlen(the->hist[the->i]) + ft_strlen(ft_where(0, NULL)) - 1);
	n_line = n_line / w.ws_col;
	if (move < 0 && j_line != 0)
	{
		the->j -= w.ws_col;
		ft_putstr_fd(tgetstr("up", NULL), 0);
		while (the->j < 0)
		{
			the->j++;
			ft_putstr_fd(tgetstr("nd", NULL), 0);
		}
	}
	else if (move > 0 && j_line < n_line)
	{
		move = the->j;
		the->j += w.ws_col;
		move = ft_hist_jump_2(move, w, the);
		the->j = move;
	}
	else
		ft_putstr_fd(tgetstr("bl", NULL), 0);
}
