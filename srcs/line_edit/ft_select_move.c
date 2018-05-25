/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 09:58:36 by swann             #+#    #+#             */
/*   Updated: 2018/03/06 16:25:24 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_move_up(t_grl nb, int pos)
{
	if (nb.row == 1)
		return (pos);
	if ((pos - 1) % nb.row != 0 && pos != 1)
		pos--;
	else
	{
		pos = pos + (nb.row - 1);
		while (pos > nb.ar_len)
			pos--;
	}
	return (pos);
}

static int	ft_move_down(t_grl nb, int pos)
{
	if (nb.row == 1)
		return (pos);
	if ((pos % nb.row != 0 && pos != nb.ar_len) || pos == 1)
		pos++;
	else
	{
		if (pos != nb.ar_len)
			pos = pos - (nb.row - 1);
		else
		{
			while ((pos - 1) % nb.row != 0)
				pos--;
		}
	}
	return (pos);
}

static int	ft_move_right(t_grl nb, int pos)
{
	if (nb.col == 1)
		return (pos);
	if (pos <= ((nb.row * nb.col) - nb.row) && (pos + nb.row) <= nb.ar_len)
		pos = pos + nb.row;
	else
	{
		if (pos > ((nb.row * nb.col) - nb.row))
			pos = pos - ((nb.row * nb.col) - nb.row);
		else
			pos = (pos + nb.row) - ((nb.row * nb.col) - nb.row);
	}
	return (pos);
}

static int	ft_move_left(t_grl nb, int pos)
{
	if (nb.col == 1)
		return (pos);
	if (pos > nb.row)
		pos = pos - nb.row;
	else
	{
		pos = pos + ((nb.row * nb.col) - nb.row);
		while (pos > nb.ar_len)
			pos = pos - nb.row;
	}
	return (pos);
}

int			ft_move(t_grl nb, int pos, char *entry)
{
	if (entry[2] == 65)
		pos = ft_move_up(nb, pos);
	else if (entry[2] == 66)
		pos = ft_move_down(nb, pos);
	else if (entry[2] == 67)
		pos = ft_move_right(nb, pos);
	else if (entry[2] == 68)
		pos = ft_move_left(nb, pos);
	return (pos);
}
