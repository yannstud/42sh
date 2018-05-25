/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 15:10:48 by slegros           #+#    #+#             */
/*   Updated: 2018/05/19 15:34:05 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		ft_get_iaccess_norme(char *cmd)
{
	if (is_reg(cmd) == 1 && access(cmd, X_OK) != -1)
		return (-1);
	else
		return (-2);
}

static int		ft_get_iaccess(char **path, char *cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	if (path != NULL)
	{
		while (path[i] != NULL)
		{
			tmp = ft_strjoin(path[i], "/");
			tmp = ft_strjoinfree(tmp, cmd, 1);
			if (access(tmp, F_OK | X_OK) != -1)
			{
				ft_strdel(&tmp);
				return (i);
			}
			i++;
			free(tmp);
		}
	}
	if (access(cmd, F_OK) != -1)
		return (ft_get_iaccess_norme(cmd));
	return (-3);
}

static char		*ft_getpath_error(int i, char *cmd)
{
	if (i == -2)
	{
		ft_putstr_col_fd("42sh: Permission denied: ", YEL, 2);
		ft_putendl_col_fd(cmd, YEL, 2);
		ft_exit_value(1, 126);
	}
	else
	{
		ft_putstr_col_fd("42sh: Command not found: ", YEL, 2);
		ft_putendl_col_fd(cmd, YEL, 2);
		ft_exit_value(1, 127);
	}
	return (NULL);
}

char			*ft_getpath(char *cmd, char **env)
{
	char	*path;
	char	**multipath;
	int		i;

	multipath = NULL;
	if ((path = ft_get_elem(env, "PATH")) != NULL)
		multipath = ft_strsplit(path, ':');
	i = ft_get_iaccess(multipath, cmd);
	free(path);
	if (i >= 0)
	{
		path = ft_strjoin(multipath[i], "/");
		path = ft_strjoinfree(path, cmd, 1);
	}
	else if (i == -1)
		path = ft_strdup(cmd);
	else
		path = ft_getpath_error(i, cmd);
	if (multipath != NULL)
		multipath = ft_dbarr_free(multipath);
	return (path);
}
