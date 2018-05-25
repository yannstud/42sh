/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:11:32 by swann             #+#    #+#             */
/*   Updated: 2018/05/15 17:43:14 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				ft_cd_error(int mode, char opt, char *str, char *tmp)
{
	ft_putstr_col_fd("21sh: cd: ", YEL, 2);
	if (mode == 1)
	{
		ft_putstr_col_fd("-", YEL, 2);
		ft_putchar_col_fd(opt, YEL, 2);
		ft_putendl_col_fd(": invalid option", YEL, 2);
		ft_putendl_col_fd("cd: usage: cd [-L|-P] [dir]", YEL, 2);
	}
	else if (mode == 2 || mode == 3 || mode == 4 || mode == 5 || mode == 6)
	{
		ft_putstr_col_fd(str, YEL, 2);
		if (mode == 2)
			ft_putendl_col_fd(" not set", YEL, 2);
		else
		{
			if (mode == 3)
				ft_putendl_col_fd(": No such file or directory", YEL, 2);
			mode == 4 ? ft_putendl_col_fd(": Permission denied", YEL, 2) : 0;
			mode == 5 ? ft_putendl_col_fd(": Not a directory", YEL, 2) : 0;
			mode == 6 ? ft_putendl_col_fd(": Unable to proceed", YEL, 2) : 0;
			free(tmp);
		}
	}
	return (1);
}

static char		ft_cd_get_opt(char *cmdopt)
{
	int		i;
	char	opt;

	if (cmdopt == NULL)
		opt = 'L';
	else
	{
		i = -1;
		while (cmdopt[++i] != '\0')
		{
			if (cmdopt[i] != 'L' || cmdopt[i] != 'P')
				return (cmdopt[i]);
		}
		opt = cmdopt[i - 1];
	}
	return (opt);
}

static int		ft_cd_spe(char *mode, char opt)
{
	char	*path;
	char	**env;
	int		i;

	env = ft_env(NULL, 0);
	if ((i = ft_get_elemi(env, mode)) != -1)
	{
		path = ft_strsub(env[i], ft_strlen(mode) + 1,
			ft_strlen(env[i]) - (ft_strlen(mode) + 1));
		if (ft_strcmp(mode, "OLDPWD") == 0)
			return (ft_cd_path(path, opt, 2));
		return (ft_cd_path(path, opt, 1));
	}
	else
		return (ft_cd_error(2, 0, mode, NULL));
}

static char		*ft_cd_rel_home(char *cmdargs, char **env)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	if ((i = ft_get_elemi(env, "HOME")) != -1)
	{
		tmp = ft_strsub(env[i], 5, ft_strlen(env[i]) - 5);
		if (tmp[ft_strlen(tmp) - 1] != '/')
			tmp = ft_strjoinfree(tmp, "/", 1);
		tmp2 = ft_strsub(cmdargs, 2, ft_strlen(cmdargs) - 2);
		tmp2 = ft_strjoinfree(tmp, tmp2, 3);
		return (tmp2);
	}
	else
		return (NULL);
}

int				ft_exec_cd(t_blt cmd)
{
	char	opt;
	char	*tmp;

	opt = ft_cd_get_opt(cmd.opt);
	if (opt != 'L' && opt != 'P')
		return (ft_cd_error(1, opt, NULL, NULL));
	if (cmd.args == NULL || ft_strcmp(cmd.args[0], "~") == 0)
		return (ft_cd_spe("HOME", opt));
	else if (ft_strcmp(cmd.args[0], "-") == 0)
		return (ft_cd_spe("OLDPWD", opt));
	else
	{
		if (ft_strncmp(cmd.args[0], "~/", 2) == 0)
		{
			if ((tmp = ft_cd_rel_home(cmd.args[0], ft_env(NULL, 0))) == NULL)
				return (ft_cd_error(2, 0, "HOME", NULL));
			else
			{
				free(cmd.args[0]);
				cmd.args[0] = ft_strdup(tmp);
				free(tmp);
			}
		}
		return (ft_cd_path(cmd.args[0], opt, 0));
	}
}
