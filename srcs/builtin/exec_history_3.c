/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_history_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:33:33 by slegros           #+#    #+#             */
/*   Updated: 2018/05/23 14:17:21 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_history_error_2(int mode, char c)
{
	ft_putstr_col_fd("42sh: history: -", YEL, 2);
	ft_putchar_col_fd(c, YEL, 2);
	if (mode == 3)
		ft_putendl_col_fd(": Invalid option", YEL, 2);
	else if (mode == 5)
		ft_putendl_col_fd(": Option requires an argument", YEL, 2);
	else
		ft_putendl_col_fd(": Unable to load file", YEL, 2);
	if (mode == 3 || mode == 5 || mode == 7)
	{
		ft_putstr_col_fd("history: usage: history [-c] [-d offset] [n", YEL, 2);
		ft_putstr_col_fd("] or history -awrn [filename] or history -p", YEL, 2);
		ft_putendl_col_fd("s arg [arg...]", YEL, 2);
	}
}

int				ft_history_error(int mode, char *str, char c)
{
	if (mode == 1 || mode == 6)
	{
		ft_putstr_col_fd("42sh: history: ", YEL, 2);
		ft_putstr_col_fd(str, YEL, 2);
		if (mode == 1)
			ft_putendl_col_fd(": Numeric arguments required", YEL, 2);
		else
			ft_putendl_col_fd(": History position out of range", YEL, 2);
	}
	else if (mode == 2)
		ft_putendl_col_fd("42sh: history: Too many arguments", YEL, 2);
	else if (mode == 3 || mode == 5 || mode == 7)
		ft_history_error_2(mode, c);
	else if (mode == 4)
	{
		ft_putstr_col_fd("42sh: history: cannot use more than one of ", YEL, 2);
		ft_putendl_col_fd("-cdanrwps", YEL, 2);
	}
	return (1);
}

static char		**ft_filecontent_2(char **env, int i)
{
	char	*tmp;
	char	**cont;

	tmp = ft_strsub(env[i], 5, ft_strlen(env[i]) - 5);
	if (tmp[ft_strlen(tmp) - 1] != '/')
		tmp = ft_strjoinfree(tmp, "/", 1);
	if (access(tmp, F_OK) != -1 && access(tmp, X_OK) != -1)
	{
		tmp = ft_strjoinfree(tmp, ".42sh_history", 1);
		cont = ft_hist_getcontent(tmp, 1);
		free(tmp);
		if (cont == NULL)
			return (NULL);
		else
			return (cont);
	}
	else
	{
		free(tmp);
		return (NULL);
	}
}

char			**ft_filecontent(void)
{
	char	**env;
	int		i;

	env = ft_env(NULL, 0);
	if ((i = ft_get_elemi(env, "HOME")) != -1)
		return (ft_filecontent_2(env, i));
	else
		return (NULL);
}
