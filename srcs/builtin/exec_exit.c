/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 12:33:08 by swann             #+#    #+#             */
/*   Updated: 2018/05/14 14:15:38 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		ft_exit_error(int mode)
{
	if (mode == 1)
		ft_putendl_col_fd("42sh: exit: Too many arguments", YEL, 2);
	else
		ft_putendl_col_fd("42sh: exit: Numeric arguments required", YEL, 2);
	return (1);
}

static void		ft_exit_norme(int val)
{
	t_h		the;

	the = ft_history(0, NULL, 0);
	ft_hist_savefile(the.hist, ft_env(NULL, 0));
	ft_term_reset();
	ft_putchar('\n');
	ft_hello_bye(BRED);
	exit(val);
}

int				ft_exec_exit(t_blt cmd)
{
	int		val;
	int		i;

	if (cmd.args == NULL)
		val = ft_exit_value(0, 0);
	else
	{
		i = -1;
		while (cmd.args[0][++i] != '\0')
		{
			if (!(ft_isdigit(cmd.args[0][i]) == 1 || ((cmd.args[0][0] == '+'
				|| cmd.args[0][0] == '-') && ft_strlen(cmd.args[0]) > 1)))
			{
				ft_exit_error(2);
				ft_exit_norme(128);
			}
		}
		if (ft_dbarrlen(cmd.args) > 1)
			return (ft_exit_error(1));
		val = ft_atoi(cmd.args[0]);
	}
	if (val < 0 || val > 255)
		val = val % 256;
	ft_exit_norme(val);
	return (0);
}
