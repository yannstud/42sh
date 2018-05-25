/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 08:44:08 by slegros           #+#    #+#             */
/*   Updated: 2018/04/30 17:32:14 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_hist_tab_write_3(int in, char *name, t_wsize w, t_h *the)
{
	while (in < (int)ft_strlen(name))
	{
		the->hist[the->i] = ft_strinsert(the->hist[the->i], name[in], the->j);
		the->j += 1;
		if (the->j == (int)ft_strlen(the->hist[the->i]))
		{
			ft_putchar_fd(name[in], 0);
			if ((the->j + ft_strlen(ft_where(0, NULL))) % w.ws_col == 0)
			{
				ft_putstr_fd(tgetstr("cr", NULL), 0);
				ft_putstr_fd(tgetstr("do", NULL), 0);
				ft_putstr_fd(tgetstr("cd", NULL), 0);
			}
		}
		else
			ft_hist_print_spe(the, 1);
		in++;
	}
	if (is_dir(name) == 1)
		ft_hist_edit(the, "/", 3);
}

void			ft_hist_tab_write_2(t_h *the)
{
	while (the->j - 1 >= 0 && the->hist[the->i][the->j - 1] >= 33
		&& the->hist[the->i][the->j - 1] <= 126)
	{
		if (the->hist[the->i][the->j] == '$'
			|| the->hist[the->i][the->j - 1] == '&'
			|| the->hist[the->i][the->j - 1] == ';'
			|| the->hist[the->i][the->j - 1] == '|'
			|| the->hist[the->i][the->j - 1] == '`'
			|| the->hist[the->i][the->j - 1] == ')'
			|| (the->hist[the->i][the->j - 1] == '-'
			&& the->hist[the->i][the->j - 2] == ' ')
			|| the->hist[the->i][the->j - 1] == '<'
			|| the->hist[the->i][the->j - 1] == '>')
		{
			break ;
		}
		the->j--;
		the->hist[the->i] = ft_strrem(the->hist[the->i], the->j);
		ft_hist_move_left(the, 1);
	}
}

void			ft_hist_tab_write(char **name, t_h *the)
{
	int			jn;
	t_wsize		w;

	ft_hist_tab_write_2(the);
	ft_putstr_fd(tgetstr("ce", NULL), 0);
	jn = -1;
	w = ft_get_winsize(0);
	while (name[++jn] != NULL)
	{
		if (jn != 0)
		{
			the->hist[the->i] = ft_strinsert(the->hist[the->i], ' ', the->j);
			the->j += 1;
			ft_putchar_fd(' ', 0);
		}
		ft_hist_tab_write_3(0, name[jn], w, the);
	}
}

void			ft_hist_tab_2(t_h *the)
{
	int		in;
	char	*t1;
	char	*t2;

	in = the->j - 1;
	t1 = ft_strnew(0);
	t2 = ft_strdup(the->hist[the->i]);
	while (in >= 0 && t2[in] >= 33 && t2[in] <= 126)
	{
		if (t2[in] != 39 && t2[in] != 34 && t2[in] != 92)
			t1 = ft_strinsert(t1, t2[in], 0);
		if (t2[in] == '$' || t2[in] == '&' || t2[in] == ';' || t2[in] == '|'
			|| t2[in] == '`' || t2[in] == ')' || (t2[in] == '-'
			&& t2[in - 1] == ' ') || t2[in] == '<' || t2[in] == '>')
		{
			break ;
		}
		in--;
	}
	ft_hist_tab_search(t1, the, in, ft_get_winsize(0));
	free(t2);
}

void			ft_hist_tab(t_h *the)
{
	int		in;

	if (ft_onlyspc(the->hist[the->i]) == 1)
	{
		in = -1;
		while (++in < 4)
			ft_hist_edit(the, " ", 3);
	}
	else
		ft_hist_tab_2(the);
}
