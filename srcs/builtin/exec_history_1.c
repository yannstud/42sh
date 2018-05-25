/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_history_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 10:08:08 by swann             #+#    #+#             */
/*   Updated: 2018/05/23 12:48:51 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		ft_history_danwrc(char opt, char **args)
{
	if (opt == 'd')
	{
		if (args == NULL)
			return (ft_history_error(5, NULL, opt));
		return (ft_history_d(args[0]));
	}
	else if (opt == 'a')
		return (ft_history_a(args, 'a'));
	else if (opt == 'n')
		return (ft_history_n(args));
	else if (opt == 'w')
		return (ft_history_w(args, 'w'));
	else if (opt == 'r')
		return (ft_history_r(args));
	else
	{
		ft_history(19, NULL, 0);
		return (0);
	}
}

static int		ft_print_history(int val)
{
	t_h		the;
	int		i;
	int		spc;

	the = ft_history(0, NULL, 0);
	if (val == -1)
		i = -1;
	else
		i = (ft_dbarrlen(the.hist) - 1) - val;
	i = (i < -1) ? -1 : i;
	while (the.hist[++i] != NULL)
	{
		spc = ft_nbrlen(i + 1) - 1;
		while (++spc <= 4)
			ft_putchar(' ');
		ft_putnbr(i + 1);
		ft_putstr("  ");
		ft_putendl(the.hist[i]);
	}
	return (0);
}

static void		ft_history_ps(char **args, char opt)
{
	char	*tmp;

	if (opt == 'p')
	{
		ft_dbarrprint(args);
		ft_history(20, NULL, 0);
	}
	else
	{
		tmp = ft_dbarrtostr(args, ' ');
		ft_history(21, tmp, 0);
		free(tmp);
	}
}

static int		ft_history_opt(char *opt, char **args)
{
	int		i;

	i = -1;
	while (opt[++i] != '\0')
	{
		if (opt[i] != 'c' && opt[i] != 'd' && opt[i] != 'a' && opt[i] != 'n'
			&& opt[i] != 'w' && opt[i] != 'r' && opt[i] != 'p' && opt[i] != 's')
			return (ft_history_error(3, NULL, opt[i]));
	}
	if (ft_strlen(opt) > 1)
		return (ft_history_error(4, NULL, 0));
	else if (opt[0] == 'p' || opt[0] == 's')
	{
		if (args != NULL)
			ft_history_ps(args, opt[0]);
		else
			return (ft_history_error(5, NULL, opt[0]));
	}
	else
		return (ft_history_danwrc(opt[0], args));
	return (0);
}

int				ft_exec_history(t_blt cmd)
{
	int		i;

	if (cmd.opt == NULL)
	{
		if (cmd.args != NULL)
		{
			i = -1;
			while (cmd.args[0][++i] != '\0')
			{
				if (!(ft_isdigit(cmd.args[0][i]) == 1
					|| (cmd.args[0][0] == '+' && ft_strlen(cmd.args[0]) > 1)))
					return (ft_history_error(1, cmd.args[0], 0));
			}
			if (ft_dbarrlen(cmd.args) > 1)
				return (ft_history_error(2, NULL, 0));
			return (ft_print_history(ft_atoi(cmd.args[0])));
		}
		return (ft_print_history(-1));
	}
	else
		return (ft_history_opt(cmd.opt, cmd.args));
}
