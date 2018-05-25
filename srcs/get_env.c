/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swann <swann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 18:02:19 by slegros           #+#    #+#             */
/*   Updated: 2018/05/22 14:13:44 by swann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		**ft_setnewenv(void)
{
	char			*pwd;
	char			*tmp;
	char			**env;
	struct passwd	*user;

	if (!(env = (char **)malloc(sizeof(char *) * (7 + 1))))
		return (NULL);
	user = getpwuid(getuid());
	env[1] = ft_strjoin("USER=", user->pw_name);
	env[2] = ft_strjoin("HOME=", user->pw_dir);
	env[3] = ft_strjoin("SHELL=", user->pw_shell);
	pwd = ft_strdup("PWD=");
	tmp = getcwd(NULL, 0);
	pwd = ft_strjoinfree(pwd, tmp, 1);
	env[4] = ft_strdup(pwd);
	env[5] = ft_strdup("SHLVL=1");
	env[6] = ft_strdup("_=/usr/bin/env");
	env[0] = ft_strdup("TERM=xterm");
	env[7] = NULL;
	ft_strdel(&tmp);
	ft_strdel(&pwd);
	return (env);
}

static char		**ft_setenv_user(char **env)
{
	struct passwd	*user;
	int				i;
	char			*shell;
	char			*usr;
	char			*home;

	user = getpwuid(getuid());
	usr = ft_strjoin("USER=", user->pw_name);
	home = ft_strjoin("HOME=", user->pw_dir);
	shell = ft_strjoin("SHELL=", user->pw_shell);
	if ((i = ft_get_elemi(env, "USER")) == -1)
		env = ft_dbarr_add(env, usr);
	if ((i = ft_get_elemi(env, "HOME")) == -1)
		env = ft_dbarr_add(env, home);
	if ((i = ft_get_elemi(env, "SHELL")) == -1)
		env = ft_dbarr_add(env, shell);
	free(usr);
	free(home);
	free(shell);
	return (env);
}

static char		**ft_setenv_shlvl(char **env)
{
	char	*shlvl;
	int		lvl;
	int		i;

	if ((shlvl = ft_get_elem(env, "SHLVL")) != NULL)
	{
		lvl = ft_atoi(shlvl);
		lvl = (lvl <= 0) ? 1 : lvl + 1;
		i = ft_get_elemi(env, "SHLVL");
		free(shlvl);
		free(env[i]);
		env[i] = ft_itoa(lvl);
		env[i] = ft_strjoinfree("SHLVL=", env[i], 2);
	}
	else
		env = ft_dbarr_add(env, "SHLVL=1");
	return (env);
}

static char		**ft_setenv(char **env)
{
	int		i;
	char	*pwd;
	char	*tmp;

	env = ft_setenv_user(env);
	if ((i = ft_get_elemi(env, "PWD")) == -1)
	{
		pwd = ft_strdup("PWD=");
		tmp = getcwd(NULL, 0);
		pwd = ft_strjoinfree(pwd, tmp, 1);
		env = ft_dbarr_add(env, pwd);
		ft_strdel(&tmp);
		ft_strdel(&pwd);
	}
	if ((i = ft_get_elemi(env, "TERM")) == -1)
		env = ft_dbarr_add(env, "TERM=xterm");
	env = ft_setenv_shlvl(env);
	return (env);
}

char			**ft_get_env(void)
{
	extern char		**environ;
	char			**env;

	if (environ && environ[0] != NULL)
	{
		env = ft_dbarrdup(environ);
		env = ft_setenv(env);
	}
	else
		env = ft_setnewenv();
	return (env);
}
