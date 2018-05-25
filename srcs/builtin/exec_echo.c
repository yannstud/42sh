/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jukuntzm <jukuntzm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 11:43:49 by slegros           #+#    #+#             */
/*   Updated: 2018/05/15 17:30:06 by jukuntzm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		ft_echo_home(char **env, char *entry)
{
	char	*tmp;
	int		dsp;

	dsp = 0;
	if ((tmp = ft_get_elem(env, "HOME")) != NULL)
	{
		if (ft_strlen(entry) > 1 && entry[1] != '/')
			dsp = 0;
		else
		{
			if (ft_strlen(entry) > 1 && entry[1] == '/')
				tmp = ft_strjoinfree(tmp, ft_strsub(entry, 1,
					ft_strlen(entry) - 1), 3);
			ft_putstr(tmp);
			dsp = 1;
		}
		free(tmp);
	}
	return (dsp);
}

static int		ft_echo_var(char **env, char *entry)
{
	char	*tmp;
	int		dsp;
	int		j;

	dsp = 0;
	j = -1;
	if (entry[1] == '?')
	{
		ft_putnbr(ft_exit_value(0, 0));
		ft_putstr((ft_strlen(entry) != 2) ? entry + 2 : NULL);
		return (1);
	}
	while (env[++j] != NULL)
	{
		tmp = ft_strjoin("$", env[j]);
		if (ft_strncmp(entry, tmp, ft_strlen(entry)) == 0)
		{
			tmp = ft_strsubf(tmp, ft_strichr(tmp, '=') + 1,
				ft_strlen(tmp) - (ft_strichr(tmp, '=') + 1));
			ft_putstr(tmp);
			dsp = 1;
		}
		free(tmp);
	}
	return (dsp);
}

int				ft_exec_echo(char **entry)
{
	int		i;
	int		dsp;

	if (entry[1] != NULL && ft_strcmp(entry[1], "-n") == 0)
		i = 1;
	else
		i = 0;
	while (entry[++i] != NULL)
	{
		if (entry[i][0] == '$' && entry[i][1] != '\0')
			dsp = ft_echo_var(ft_env(NULL, 0), entry[i]);
		else if (entry[i][0] == '~')
			dsp = ft_echo_home(ft_env(NULL, 0), entry[i]);
		else
		{
			ft_putstr(entry[i]);
			dsp = 1;
		}
		if (entry[i + 1] != NULL && dsp == 1)
			ft_putchar(' ');
	}
	if (!(entry[1] != NULL && ft_strcmp(entry[1], "-n") == 0))
		ft_putchar('\n');
	return (0);
}
