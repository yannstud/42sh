/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 10:02:03 by swann             #+#    #+#             */
/*   Updated: 2018/05/12 13:35:58 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_print_elem(int i, int pos, int *select, char **ar_list)
{
	if (i == (pos - 1))
		ft_putstr_fd(tgetstr("us", NULL), 0);
	if (select[i] == 1)
		ft_putstr_fd(tgetstr("mr", NULL), 0);
	if (i == (pos - 1))
		ft_putstr_col_fd(ar_list[i], YEL, 0);
	else if (select[i] == 1)
		ft_putstr_col_fd(ar_list[i], GRN, 0);
	else
		ft_putstr_fd(ar_list[i], 0);
	ft_putstr_fd(tgetstr("me", NULL), 0);
}

static int		ft_get_pls(t_grl nb)
{
	int		pls;

	if (nb.col > 1 && (nb.row * nb.col) != nb.ar_len)
		pls = (nb.row > 1) ? nb.ar_len % nb.row : 1;
	else
		pls = nb.row;
	return (pls);
}

void			ft_print(char **ar_list, t_grl nb, int pos, t_wsize w)
{
	t_prt	val;

	if (w.ws_row - 2 < nb.row)
		ft_putstr_fd("Can't display elements 2.", 2);
	else
	{
		val.i = 0;
		val.row = -1;
		val.select = ft_sel(nb.ar_len, -2, 0);
		val.pls = ft_get_pls(nb);
		while (++val.row < nb.row)
		{
			val.i = 0 + val.row;
			val.col = (val.pls > 0) ? -1 : 0;
			val.pls--;
			while (++val.col < nb.col)
			{
				ft_print_elem(val.i, pos, val.select, ar_list);
				ft_print_space(nb.max_len, ft_strlen(ar_list[val.i]));
				val.i += nb.row;
			}
			ft_putchar_fd('\n', 0);
		}
	}
}
