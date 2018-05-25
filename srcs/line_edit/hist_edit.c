/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 02:52:32 by slegros           #+#    #+#             */
/*   Updated: 2018/05/23 14:04:42 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			*ft_hist_upk_save(char *to_save, int mode)
{
	static char		*save;

	if (mode == 1)
	{
		if (save)
			free(save);
		save = ft_strdup(to_save);
	}
	return (save);
}

static void		ft_hist_upk_copy(t_h *the)
{
	char		*tmp;
	int			in;
	t_wsize		w;

	tmp = ft_strdup(ft_hist_upk_save(NULL, 2));
	in = -1;
	w = ft_get_winsize(0);
	while (tmp[++in] != '\0')
	{
		the->hist[the->i] = ft_strinsert(the->hist[the->i], tmp[in], the->j);
		the->j += 1;
		if (the->j == (int)ft_strlen(the->hist[the->i]))
		{
			ft_putchar_fd(tmp[in], 0);
			if ((the->j + ft_strlen(ft_where(0, NULL))) % w.ws_col == 0)
			{
				ft_putstr_fd(tgetstr("cr", NULL), 0);
				ft_putstr_fd(tgetstr("do", NULL), 0);
				ft_putstr_fd(tgetstr("cd", NULL), 0);
			}
		}
		else
			ft_hist_print_spe(the, 1);
	}
	free(tmp);
}

void			ft_hist_upk(t_h *the, int key)
{
	char	*tmp;

	ft_sigupk(1, 1);
	if ((key == 21 || key == 11) && ft_strlen(the->hist[the->i]) != 0
		&& the->j != (int)ft_strlen(the->hist[the->i]))
	{
		tmp = ft_strsub(the->hist[the->i], the->j,
			ft_strlen(the->hist[the->i]) - the->j);
		ft_hist_upk_save(tmp, 1);
		if (key == 11)
		{
			the->hist[the->i] = ft_strsubf(the->hist[the->i], 0, the->j);
			ft_hist_print_spe(the, 2);
		}
		free(tmp);
	}
	else if (key == 16 && ft_hist_upk_save(NULL, 0))
		ft_hist_upk_copy(the);
	else
		ft_putstr_fd(tgetstr("bl", NULL), 0);
	ft_sigupk(1, 0);
}

static void		ft_hist_insert(t_h *the, char *buf)
{
	t_wsize		w;

	the->hist[the->i] = ft_strinsert(the->hist[the->i], buf[0], the->j);
	the->j += 1;
	w = ft_get_winsize(0);
	if (the->j == (int)ft_strlen(the->hist[the->i]))
	{
		ft_putchar_fd(buf[0], 0);
		if ((the->j + ft_strlen(ft_where(0, NULL))) % w.ws_col == 0)
		{
			ft_putstr_fd(tgetstr("cr", NULL), 0);
			ft_putstr_fd(tgetstr("do", NULL), 0);
			ft_putstr_fd(tgetstr("cd", NULL), 0);
		}
	}
	else
		ft_hist_print_spe(the, 1);
}

void			ft_hist_edit(t_h *the, char *buf, int mode)
{
	t_wsize		w;
	int			mod;

	w = ft_get_winsize(0);
	if (mode == 3)
		ft_hist_insert(the, buf);
	else if (mode == 20 || mode == 21)
		the->hist = ft_dbarr_del(the->hist, ft_dbarrlen(the->hist) - 1);
	else
	{
		if ((the->j != 0 && mode == 8)
			|| (the->j != (int)ft_strlen(the->hist[the->i]) && mode == 9))
		{
			mod = 0;
			if (mode == 8)
				mod = 1;
			the->j -= mod;
			the->hist[the->i] = ft_strrem(the->hist[the->i], the->j);
			ft_hist_print_spe(the, 2 + mod);
		}
		else
			ft_putstr_fd(tgetstr("bl", NULL), 0);
	}
	if (mode == 21 || mode == 27)
		the->hist = ft_dbarr_add(the->hist, buf);
}
