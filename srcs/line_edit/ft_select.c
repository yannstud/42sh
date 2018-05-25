/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 09:17:25 by swann             #+#    #+#             */
/*   Updated: 2018/05/12 14:50:32 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				ft_get_pos(int pos, int mode)
{
	static int	pos_save;

	if (mode == 1)
		pos_save = pos;
	return (pos_save);
}

static int		ft_reset(char *entry, t_grl nb)
{
	int		i;

	i = -1;
	while (++i < 4)
		entry[i] = '\0';
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	return (nb.row);
}

static int		ft_select_make_space(t_grl nb, t_wsize w)
{
	int		i;

	i = -1;
	ft_button_select(1, 1);
	ft_putstr_fd(tgetstr("vi", NULL), 0);
	if (w.ws_row - 2 < nb.row)
	{
		ft_putstr_fd("Can't display elements 1.", 2);
		ft_putstr_fd(tgetstr("cr", NULL), 0);
		read(0, NULL, 1);
		ft_button_select(1, 0);
		ft_add_args(NULL, ft_sel(nb.ar_len, -2, 0), 2);
		return (-1000);
	}
	while (++i < nb.row)
		ft_putstr_fd(tgetstr("do", NULL), 0);
	while (--i >= 0)
		ft_putstr_fd(tgetstr("up", NULL), 0);
	return (1);
}

static void		ft_select_norme(void)
{
	ft_sel(0, -4, 0);
	ft_button_select(1, 0);
	ft_putstr_fd(tgetstr("ve", NULL), 0);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
}

char			**ft_select(char **list)
{
	char	entry[4];
	int		pos;
	t_grl	nb;
	int		*select;
	int		i;

	pos = 1;
	ft_get_pos(pos, 1);
	select = ft_sel(ft_dbarrlen(list), -1, 0);
	nb = ft_get_nb(list, ft_get_winsize(1));
	pos = ft_select_make_space(nb, ft_get_winsize(0));
	while (pos != -1000)
	{
		nb = ft_get_nb(list, ft_get_winsize(0));
		i = ft_reset(entry, nb);
		ft_print(list, nb, pos, ft_get_winsize(0));
		read(0, entry, 3);
		pos = ft_set_pos(entry, ft_get_nb(list,
			ft_get_winsize(1)), pos, list);
		ft_get_pos(pos, 1);
		while (--i >= 0)
			ft_putstr_fd(tgetstr("up", NULL), 0);
	}
	ft_select_norme();
	return (ft_add_args(NULL, NULL, 0));
}
