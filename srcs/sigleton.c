/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigleton.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:43:10 by slegros           #+#    #+#             */
/*   Updated: 2018/05/15 17:44:45 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_path(int mode, char *path)
{
	static char		*sav_path;

	if (mode == 1)
		sav_path = getcwd(NULL, 0);
	else if (mode == 2)
	{
		free(sav_path);
		sav_path = ft_strdup(path);
	}
	return (sav_path);
}

int		ft_button_select(int mode, int val)
{
	static int		sav_val;

	if (mode == 1)
		sav_val = val;
	return (sav_val);
}

int		ft_exit_value(int mode, int val)
{
	static int		sav_val;

	if (mode == 1)
		sav_val = val;
	return (sav_val);
}

char	**ft_env(char **env, int mode)
{
	static char		**save_env;

	if (mode == 1 || mode == 2)
	{
		if (mode == 2)
			save_env = ft_dbarr_free(save_env);
		save_env = ft_dbarrdup(env);
	}
	return (save_env);
}

int		ft_button_line(int mode, int val)
{
	static int		sav_val;

	if (mode == 1)
		sav_val = val;
	return (sav_val);
}
