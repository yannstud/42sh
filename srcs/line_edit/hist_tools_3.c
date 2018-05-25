/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_tools_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:59:47 by swann             #+#    #+#             */
/*   Updated: 2018/05/23 14:17:44 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		*ft_hist_makecontent(char **hist)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strnew(0);
	while (hist[++i] != NULL)
	{
		tmp = ft_strjoinfree(tmp, hist[i], 1);
		tmp = ft_strjoinfree(tmp, "\n", 1);
	}
	return (tmp);
}

int				ft_hist_savefile_bis(char **hist, char *path)
{
	int		fd;
	char	*tmp;

	if (access(path, F_OK) != -1 && access(path, W_OK) != -1)
	{
		tmp = ft_hist_makecontent(hist);
		if ((fd = open(path, O_CREAT | O_WRONLY, 0644)) != -1)
			write(fd, tmp, ft_strlen(tmp));
		close(fd);
		free(tmp);
		return (0);
	}
	return (1);
}

int				ft_hist_savefile(char **hist, char **env)
{
	int		i;
	char	*path;
	int		fd;
	char	*tmp;

	if ((i = ft_get_elemi(env, "HOME")) != -1)
	{
		path = ft_strsub(env[i], 5, ft_strlen(env[i]) - 5);
		if (path[ft_strlen(path) - 1] != '/')
			path = ft_strjoinfree(path, "/", 1);
		if (access(path, F_OK) != -1 && access(path, W_OK) != -1)
		{
			path = ft_strjoinfree(path, ".42sh_history", 1);
			tmp = ft_hist_makecontent(hist);
			if ((fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644)) != -1)
				write(fd, tmp, ft_strlen(tmp));
			close(fd);
			free(tmp);
			free(path);
			return (0);
		}
		free(path);
		return (1);
	}
	return (1);
}

static void		ft_hist_getfile_2(t_h *the, char *tmp)
{
	char	**cont;

	cont = ft_hist_getcontent(tmp, 1);
	if (cont == NULL)
		ft_hist_newhist(the);
	else
	{
		the->hist = ft_dbarrdup(cont);
		the->i = ft_dbarrlen(the->hist);
		the->start = ft_dbarrlen(the->hist);
		cont = ft_dbarr_free(cont);
	}
}

void			ft_hist_getfile(t_h *the)
{
	char	**env;
	int		i;
	char	*tmp;

	env = ft_env(NULL, 0);
	if ((i = ft_get_elemi(env, "HOME")) != -1)
	{
		tmp = ft_strsub(env[i], 5, ft_strlen(env[i]) - 5);
		if (tmp[ft_strlen(tmp) - 1] != '/')
			tmp = ft_strjoinfree(tmp, "/", 1);
		if (access(tmp, F_OK) != -1 && access(tmp, X_OK) != -1)
		{
			tmp = ft_strjoinfree(tmp, ".42sh_history", 1);
			ft_hist_getfile_2(the, tmp);
		}
		else
			ft_hist_newhist(the);
		free(tmp);
	}
	else
		ft_hist_newhist(the);
}
