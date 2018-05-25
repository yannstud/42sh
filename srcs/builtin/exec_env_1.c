/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 13:58:27 by slegros           #+#    #+#             */
/*   Updated: 2018/05/23 17:50:14 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		ft_print_env(char **env)
{
	ft_dbarrprint(env);
	env = ft_dbarr_free(env);
	return (0);
}

static int		ft_exec_env_args(t_blt cmd, char **tmp_env, int i, t_cmd *cmds)
{
	char	**tabz;
	int		ret;

	if (i == ft_dbarrlen(cmd.args))
		return (ft_print_env(tmp_env));
	else
	{
		if (ft_isbuiltin(cmd.args[i]) == 1)
		{
			tmp_env = ft_dbarr_free(tmp_env);
			return (ft_env_error(cmd.args[i], 5));
		}
		tabz = ft_dbarrnew(0);
		while (cmd.args[i] != NULL)
		{
			tabz = ft_dbarr_add(tabz, cmd.args[i]);
			i++;
		}
		ret = ft_exec_env_args_2(tabz, tmp_env, cmds);
		tmp_env = ft_dbarr_free(tmp_env);
		tabz = ft_dbarr_free(tabz);
		return (ret);
	}
}

static char		**ft_exec_env_add(char **tmp_env, char *str)
{
	char	*name;
	int		i;

	name = ft_strsub(str, 0, ft_strichr(str, '='));
	if (ft_check_name(name) == -1)
	{
		ft_putstr_col_fd("42sh: env: ", YEL, 2);
		ft_putstr_col_fd(name, YEL, 2);
		ft_putendl_col_fd(": Incorrect identifer", YEL, 2);
	}
	else
	{
		if ((i = ft_get_elemi(tmp_env, name)) == -1)
			tmp_env = ft_dbarr_add(tmp_env, str);
		else
			tmp_env = ft_dbarr_edit(tmp_env, str, i);
	}
	free(name);
	return (tmp_env);
}

static int		ft_exec_env(t_blt cmd, char **env, t_cmd *cmds)
{
	char	**tmp_env;
	int		i;

	if (cmd.opt != NULL)
	{
		if (ft_strcmp(cmd.opt, "i") != 0)
			return (ft_env_error(cmd.opt, 1));
		tmp_env = ft_dbarrnew(0);
	}
	else
		tmp_env = ft_dbarrdup(env);
	if (cmd.args == NULL)
		return (ft_print_env(tmp_env));
	else
	{
		i = -1;
		while (cmd.args[++i] != NULL)
		{
			if (ft_strichr(cmd.args[i], '=') > 0)
				tmp_env = ft_exec_env_add(tmp_env, cmd.args[i]);
			else
				break ;
		}
		return (ft_exec_env_args(cmd, tmp_env, i, cmds));
	}
}

int				ft_prexec_env(t_blt cmd, char **env, t_cmd *cmds)
{
	if (ft_strcmp(cmd.cmd, "env") == 0)
		return (ft_exec_env(cmd, env, cmds));
	else if (ft_strcmp(cmd.cmd, "setenv") == 0)
		return (ft_exec_setenv(cmd, env));
	else
		return (ft_exec_unsetenv(cmd, env));
}
