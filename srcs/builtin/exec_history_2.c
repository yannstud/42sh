/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_history_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:14:52 by slegros           #+#    #+#             */
/*   Updated: 2018/05/23 14:17:05 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_history_d(char *arg)
{
	int		i;
	t_h		the;
	int		nb;

	i = -1;
	the = ft_history(0, NULL, 0);
	while (arg[++i] != '\0')
	{
		if (!(ft_isdigit(arg[i]) == 1 || (arg[0] == '+' && ft_strlen(arg) > 1)))
			return (ft_history_error(6, arg, 0));
	}
	nb = ft_atoi(arg);
	if (nb < 1 || nb > ft_dbarrlen(the.hist))
		return (ft_history_error(6, arg, 0));
	else
	{
		ft_history(22, NULL, nb - 1);
		return (0);
	}
}

int		ft_history_a(char **args, char opt)
{
	char	**cont;
	t_h		the;
	int		i;

	the = ft_history(0, NULL, 0);
	if (args == NULL)
	{
		if ((cont = ft_filecontent()) == NULL)
			return (ft_history_error(7, NULL, opt));
	}
	else
	{
		if ((cont = ft_hist_getcontent(args[0], 0)) == NULL)
			return (ft_history_error(7, NULL, opt));
	}
	i = the.start - 1;
	while (++i < ft_dbarrlen(the.hist))
		cont = ft_dbarr_add(cont, the.hist[i]);
	i = (args == NULL) ? ft_hist_savefile(cont, ft_env(NULL, 0))
		: ft_hist_savefile_bis(cont, args[0]);
	cont = ft_dbarr_free(cont);
	if (i == 1)
		return (ft_history_error(7, NULL, opt));
	ft_history(26, NULL, ft_dbarrlen(the.hist));
	return (i);
}

int		ft_history_n(char **args)
{
	t_h		the;
	char	**cont;
	int		i;

	the = ft_history(0, NULL, 0);
	if (args == NULL)
	{
		if ((cont = ft_filecontent()) == NULL)
			return (ft_history_error(7, NULL, 'n'));
	}
	else
	{
		if ((cont = ft_hist_getcontent(args[0], 0)) == NULL)
			return (ft_history_error(7, NULL, 'n'));
	}
	i = (args == NULL) ? the.start - 1 : -1;
	while (++i < ft_dbarrlen(cont))
		ft_history(27, cont[i], 0);
	cont = ft_dbarr_free(cont);
	the = ft_history(0, NULL, 0);
	ft_history(26, NULL, ft_dbarrlen(the.hist));
	return (0);
}

int		ft_history_w(char **args, char opt)
{
	t_h		the;
	int		ret;
	char	**cont;

	if (args == NULL)
	{
		if ((cont = ft_filecontent()) == NULL)
			return (ft_history_error(7, NULL, opt));
	}
	else
	{
		if ((cont = ft_hist_getcontent(args[0], 0)) == NULL)
			return (ft_history_error(7, NULL, opt));
	}
	the = ft_history(0, NULL, 0);
	if (args == NULL)
		ret = ft_hist_savefile(the.hist, ft_env(NULL, 0));
	else
		ret = ft_hist_savefile_bis(the.hist, args[0]);
	cont = ft_dbarr_free(cont);
	if (ret == 1)
		return (ft_history_error(7, NULL, opt));
	ft_history(26, NULL, ft_dbarrlen(the.hist));
	return (ret);
}

int		ft_history_r(char **args)
{
	char	**cont;

	if (args == NULL)
	{
		if ((cont = ft_filecontent()) == NULL)
			return (ft_history_error(7, NULL, 'r'));
	}
	else
	{
		if ((cont = ft_hist_getcontent(args[0], 0)) == NULL)
			return (ft_history_error(7, NULL, 'r'));
	}
	cont = ft_dbarr_free(cont);
	ft_history(26, NULL, ft_dbarrlen(cont));
	ft_history(24, NULL, 0);
	return (0);
}
