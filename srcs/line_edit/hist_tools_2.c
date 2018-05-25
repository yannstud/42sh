/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_tools_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 11:53:23 by slegros           #+#    #+#             */
/*   Updated: 2018/05/23 14:15:42 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_hist_print_spe_eol(t_h *the, int j_line, t_wsize w)
{
	int			nb_line;
	int			i;
	int			val;
	int			f;

	val = (j_line == 0) ? ft_strlen(ft_where(0, NULL)) : 0;
	nb_line = (ft_strlen(the->hist[the->i]) + ft_strlen(ft_where(0, NULL)) - 1);
	nb_line /= w.ws_col;
	i = 0;
	while (j_line + i < nb_line)
	{
		ft_putstr_fd(tgetstr("do", NULL), 0);
		i++;
	}
	while (i > 0)
	{
		ft_putstr_fd(tgetstr("up", NULL), 0);
		i--;
	}
	i = -1;
	f = (the->j + ft_strlen(ft_where(0, NULL))) - ((j_line + 0) * w.ws_col);
	if (f == w.ws_col)
		f = (the->j + ft_strlen(ft_where(0, NULL))) - ((j_line + 1) * w.ws_col);
	while (++i < f)
		ft_hist_move_right(the, 0);
}

int		is_dir(char *file)
{
	struct stat		infos;

	if (stat(file, &infos) != -1 && S_ISDIR(infos.st_mode))
		return (1);
	else
		return (0);
}

void	ft_hist_merge(t_h *the)
{
	the->hist[ft_dbarrlen(the->hist) - 2] =
		ft_strjoinfree(the->hist[ft_dbarrlen(the->hist) - 2], " ", 1);
	the->hist[ft_dbarrlen(the->hist) - 2] =
		ft_strjoinfree(the->hist[ft_dbarrlen(the->hist) - 2],
		the->hist[ft_dbarrlen(the->hist) - 1], 1);
	the->hist = ft_dbarr_del(the->hist, ft_dbarrlen(the->hist) - 1);
}

void	ft_hist_newhist(t_h *the)
{
	the->i = 0;
	the->start = 0;
	if (!(the->hist = (char **)malloc(sizeof(char *) * 1)))
		return ;
	the->hist[the->i] = NULL;
}

char	**ft_hist_getcontent(char *path, int mode)
{
	int		fd;
	char	*tmp;
	char	*line;
	char	**cont;
	int		ln;

	ln = 0;
	if (mode == 1)
		fd = open(path, O_CREAT | O_RDONLY, 0644);
	else
		fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		tmp = ft_strnew(0);
		while (get_next_line(fd, &line) != 0 && ++ln < 1500)
			tmp = ft_create_line(line, tmp);
		cont = ft_strsplit(tmp, '\n');
		free(tmp);
		close(fd);
		return (cont);
	}
	return (NULL);
}
