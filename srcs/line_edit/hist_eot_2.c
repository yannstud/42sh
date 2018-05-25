/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_eot_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 06:55:38 by slegros           #+#    #+#             */
/*   Updated: 2018/05/15 15:13:08 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		ft_hist_eot_display_2(char **list, t_grl nb)
{
	int		row;
	int		pls;
	int		col;
	int		i;

	i = 0;
	row = -1;
	if (nb.col > 1 && (nb.row * nb.col) != nb.ar_len)
		pls = (nb.row > 1) ? nb.ar_len % nb.row : 1;
	else
		pls = nb.row;
	while (++row < nb.row)
	{
		i = 0 + row;
		col = (pls > 0) ? -1 : 0;
		pls--;
		while (++col < nb.col)
		{
			ft_putstr_fd(list[i], 0);
			ft_print_space(nb.max_len, ft_strlen(list[i]));
			i += nb.row;
		}
		ft_putchar_fd('\n', 0);
	}
	return (row);
}

static void		ft_hist_eot_display(char **list, t_wsize w, t_h the)
{
	int		i;
	t_grl	nb;
	int		row;

	i = 0;
	ft_putstr_fd(tgetstr("cr", NULL), 0);
	ft_putstr_fd(tgetstr("do", NULL), 0);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	nb = ft_get_nb(list, w);
	list = ft_proper_list(list);
	if (nb.row > w.ws_row - 2)
	{
		ft_putstr_fd("Too many elements", 2);
		ft_putstr_fd(tgetstr("up", NULL), 0);
		ft_putstr_fd(tgetstr("cr", NULL), 0);
	}
	else
	{
		row = ft_hist_eot_display_2(list, nb);
		while (--row > -2)
			ft_putstr_fd(tgetstr("up", NULL), 0);
	}
	i = -1;
	while (++i < ((int)(the.j + ft_strlen(ft_where(0, NULL))) % w.ws_col))
		ft_putstr_fd(tgetstr("nd", NULL), 0);
}

void			ft_hist_eot_search(char *t1, int i)
{
	char	**list;

	if (t1[0] == '&' || t1[0] == ';' || t1[0] == '|' || t1[0] == '`' || i == -1)
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
	ft_strdel(&t1);
	if (list != NULL && list[0] != NULL)
	{
		ft_hist_eot_display(list, ft_get_winsize(0),
				ft_history(0, NULL, 0));
		list = ft_dbarr_free(list);
	}
	else if (list != NULL)
		list = ft_dbarr_free(list);
}

char			**ft_hist_eot_search_cmd_init(char *t1)
{
	char	**list;

	if (!(list = (char **)malloc(sizeof(char *) * 1)))
		return (NULL);
	list[0] = NULL;
	if (ft_strncmp("cd", t1, ft_strlen(t1)) == 0)
		list = ft_dbarr_add(list, "cd");
	if (ft_strncmp("echo", t1, ft_strlen(t1)) == 0)
		list = ft_dbarr_add(list, "echo");
	if (ft_strncmp("env", t1, ft_strlen(t1)) == 0)
		list = ft_dbarr_add(list, "env");
	if (ft_strncmp("setenv", t1, ft_strlen(t1)) == 0)
		list = ft_dbarr_add(list, "setenv");
	if (ft_strncmp("unsetenv", t1, ft_strlen(t1)) == 0)
		list = ft_dbarr_add(list, "unsetenv");
	if (ft_strncmp("exit", t1, ft_strlen(t1)) == 0)
		list = ft_dbarr_add(list, "exit");
	if (ft_strncmp("history", t1, ft_strlen(t1)) == 0)
		list = ft_dbarr_add(list, "history");
	return (list);
}

char			**ft_hist_eot_search_check(char **list)
{
	if (ft_dbarrlen(list) == 0)
	{
		list = ft_dbarr_free(list);
		return (NULL);
	}
	return (list);
}
