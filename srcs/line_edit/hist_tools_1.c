/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_tools_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 12:37:01 by swann             #+#    #+#             */
/*   Updated: 2018/05/20 17:31:02 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_hist_return(t_h the, int mode)
{
	int			n_line;
	int			j_line;
	t_wsize		w;
	int			len;

	if (mode == 1)
		len = ft_dbarrlen(the.hist) - 1;
	else
		len = the.i;
	w = ft_get_winsize(0);
	j_line = (the.j + ft_strlen(ft_where(0, NULL))) / w.ws_col;
	n_line = (ft_strlen(the.hist[len]) + ft_strlen(ft_where(0, NULL)));
	n_line = n_line / w.ws_col;
	while (j_line <= n_line)
	{
		ft_putchar_fd('\n', 0);
		j_line++;
	}
	ft_putstr_fd(tgetstr("cd", NULL), 0);
}

char	**ft_hist_init(t_h *the, int mode)
{
	char	**save_hist;

	if (mode == 1 || mode == 24)
	{
		if (mode == 24)
			the->hist = ft_dbarr_free(the->hist);
		ft_hist_getfile(the);
	}
	else if (mode == 19)
	{
		the->hist = ft_dbarr_free(the->hist);
		ft_hist_newhist(the);
	}
	else
	{
		save_hist = ft_dbarrdup(the->hist);
		if (ft_dbarrlen(the->hist) == 0
			|| ft_strlen(the->hist[ft_dbarrlen(the->hist) - 1]) != 0)
			the->hist = ft_dbarr_add(the->hist, "");
		the->i = ft_dbarrlen(the->hist) - 1;
		the->j = 0;
		return (save_hist);
	}
	return (NULL);
}

char	**ft_hist_restore(char **hist, char **save_hist)
{
	int		i;
	int		len;

	i = 0;
	len = ft_dbarrlen(hist) - 1;
	while (i < len)
	{
		free(hist[i]);
		hist[i] = ft_strdup(save_hist[i]);
		i++;
	}
	return (hist);
}

void	ft_hist_print_spe(t_h *the, int mode)
{
	t_wsize		w;
	int			j_line;

	w = ft_get_winsize(0);
	if (mode == 1)
		ft_hist_move_right(the, 0);
	else if (mode == 3)
		ft_hist_move_left(the, 1);
	j_line = (the->j + ft_strlen(ft_where(0, NULL)) - 1) / w.ws_col;
	if ((ft_strlen(the->hist[the->i]) + ft_strlen(ft_where(0, NULL)) - 1)
		% w.ws_col == 0 && mode == 1)
		ft_hist_print_spe_eol(the, j_line, w);
	ft_putstr_fd(tgetstr("sc", NULL), 0);
	ft_putstr_fd(tgetstr("cr", NULL), 0);
	if ((the->j + 0 + ft_strlen(ft_where(0, NULL))) % w.ws_col == 0)
		j_line += 1;
	while (j_line > 0)
	{
		ft_putstr_fd(tgetstr("up", NULL), 0);
		j_line--;
	}
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	ft_putstr_col_fd(ft_where(0, NULL), BOLD, 0);
	ft_putstr_fd(the->hist[the->i], 0);
	ft_putstr_fd(tgetstr("rc", NULL), 0);
}

int		nbl(void)
{
	t_h		tmp;

	tmp = ft_history(0, NULL, 0);
	if (ft_strlen(tmp.hist[tmp.i]) > 0)
		return (0);
	return (1);
}
