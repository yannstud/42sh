/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:36:12 by slegros           #+#    #+#             */
/*   Updated: 2018/05/22 17:11:34 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_unsetenv_error(char *str, int mode)
{
	if (mode == 7 || mode == 8)
	{
		if (mode == 8)
		{
			ft_putstr_col_fd("42sh: unsetenv: Illegal option -- ", YEL, 2);
			ft_putchar_col_fd(str[0], YEL, 2);
			ft_putchar_col_fd('\n', YEL, 2);
		}
		else
			ft_putendl_col_fd("42sh: unsetenv: Not enough arguments", YEL, 2);
		ft_putendl_col_fd("usage: unsetenv [name]...", YEL, 2);
	}
	else if (mode == 9)
	{
		ft_putstr_col_fd("42sh: unsetenv: Incorrect identifer: ", YEL, 2);
		ft_putendl_col_fd(str, YEL, 2);
	}
}

static void		ft_setenv_error(char *str, int mode)
{
	if (mode == 2 || mode == 3)
	{
		if (mode == 3)
		{
			ft_putstr_col_fd("42sh: setenv: Illegal option -- ", YEL, 2);
			ft_putchar_col_fd(str[0], YEL, 2);
			ft_putchar_col_fd('\n', YEL, 2);
		}
		else
			ft_putendl_col_fd("42sh: setenv: Not enough arguments", YEL, 2);
		ft_putendl_col_fd("usage: setenv [name=value]...", YEL, 2);
	}
	else if (mode == 6)
	{
		ft_putstr_col_fd("42sh: setenv: Bad argument: ", YEL, 2);
		ft_putendl_col_fd(str, YEL, 2);
	}
	else
		ft_unsetenv_error(str, mode);
}

int				ft_env_error(char *str, int mode)
{
	int		i;

	if (mode == 1)
	{
		i = 0;
		while (str[i] == 'i')
			i++;
		ft_putstr_col_fd("42sh: env: Illegal option -- ", YEL, 2);
		ft_putchar_col_fd(str[i], YEL, 2);
		ft_putchar_col_fd('\n', YEL, 2);
		ft_putstr_col_fd("usage: env [-i] [name=value]... [utility", YEL, 2);
		ft_putendl_col_fd(" [argument...]]", YEL, 2);
	}
	else if (mode == 5)
	{
		ft_putstr_col_fd("42sh: env: ", YEL, 2);
		ft_putstr_col_fd(str, YEL, 2);
		ft_putendl_col_fd(": Undefined results with builtin", YEL, 2);
	}
	else
		ft_setenv_error(str, mode);
	return (1);
}
