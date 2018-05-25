/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_tab_search.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 07:54:10 by swann             #+#    #+#             */
/*   Updated: 2018/05/15 17:26:42 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** static void	this_function_move_cursor_down_then_clean_and_come_back(void)
** {
** 	ft_putstr_fd(tgetstr("sc", NULL), 0);
** 	ft_putstr_fd(tgetstr("cr", NULL), 0);
** 	ft_putstr_fd(tgetstr("do", NULL), 0);
** 	ft_putstr_fd(tgetstr("cd", NULL), 0);
** 	ft_putstr_fd(tgetstr("rc", NULL), 0);
** }
**	i = -1;
**	this_function_move_cursor_down_then_clean_and_come_back();
**	while (++i <= nline)
*/

static char		**ft_hist_sel(t_h *the, t_wsize w, int i, char **list)
{
	char	**sel;
	int		nline;

	nline = (ft_strlen(the->hist[the->i]) + ft_strlen(ft_where(0, NULL)));
	nline = nline / w.ws_col;
	while (++i <= nline)
		ft_putstr_fd(tgetstr("do", NULL), 0);
	sel = ft_select(list);
	i = -1;
	while (++i <= nline)
		ft_putstr_fd(tgetstr("up", NULL), 0);
	i = -1;
	while (++i < the->j + (int)ft_strlen(ft_where(0, NULL)))
	{
		if ((i - 2 + ft_strlen(ft_where(0, NULL))) % w.ws_col == 0)
		{
			ft_putstr_fd(tgetstr("cr", NULL), 0);
			ft_putstr_fd(tgetstr("do", NULL), 0);
		}
		else
			ft_putstr_fd(tgetstr("nd", NULL), 0);
	}
	return (sel);
}

static void		ft_hist_tab_multi(t_h *the, t_wsize w, char *t1, char **list)
{
	char	**sel;
	int		i;

	i = ((the->j + ft_strlen(ft_where(0, NULL))) / w.ws_col) - 1;
	ft_putstr_fd(tgetstr("cr", NULL), 0);
	sel = ft_hist_sel(the, w, i, list);
	if (sel[0] != NULL)
	{
		if (ft_strirchr(t1, '/') != -1)
			t1 = ft_strsubf(t1, 0, ft_strirchr(t1, '/') + 1);
		i = -1;
		while (sel[++i] != NULL)
		{
			if (ft_strirchr(t1, '/') != -1)
				sel[i] = ft_strjoinfree(t1, sel[i], 2);
		}
		ft_hist_tab_write(sel, the);
	}
	sel = ft_dbarr_free(sel);
	free(t1);
}

static char		**ft_hist_list(char *t1, int in)
{
	char	**list;

	if (t1[0] == '&' || t1[0] == ';' || t1[0] == '|'
		|| t1[0] == '`' || in == -1)
	{
		list = ft_hist_eot_search_cmd(ft_strdup(t1));
		if (list == NULL)
			list = ft_hist_eot_search_dir(ft_strdup(t1));
	}
	else if (t1[0] == '$')
	{
		list = ft_hist_eot_search_env(ft_strdup(t1));
		if (list == NULL)
			list = ft_hist_eot_search_dir(ft_strdup(t1));
	}
	else
		list = ft_hist_eot_search_dir(ft_strdup(t1));
	if (list != NULL)
		list = ft_proper_list(list);
	return (list);
}

void			ft_hist_tab_search(char *t1, t_h *the, int in, t_wsize w)
{
	char	**list;

	list = ft_hist_list(t1, in);
	if (list != NULL && list[0] != NULL)
	{
		if (ft_dbarrlen(list) > 1)
			ft_hist_tab_multi(the, w, ft_strdup(t1), list);
		else
		{
			if (ft_strirchr(t1, '/') != -1)
			{
				t1 = ft_strsubf(t1, 0, ft_strirchr(t1, '/') + 1);
				list[0] = ft_strjoinfree(t1, list[0], 2);
			}
			ft_hist_tab_write(list, the);
		}
		list = ft_dbarr_free(list);
	}
	else if (list != NULL)
		list = ft_dbarr_free(list);
	free(t1);
}
