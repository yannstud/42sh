/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 17:19:02 by swann             #+#    #+#             */
/*   Updated: 2018/05/14 16:15:59 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		**ft_proper_path_2(char *path)
{
	char	**arr;
	int		i;

	arr = ft_strsplit(path, '/');
	i = -1;
	while (arr[++i] != NULL)
	{
		if (ft_strcmp(arr[i], "..") == 0 || ft_strcmp(arr[i], ".") == 0)
		{
			if (ft_strcmp(arr[i], "..") == 0 && i > 0)
			{
				arr = ft_dbarr_del(arr, i);
				i--;
			}
			arr = ft_dbarr_del(arr, i);
			i--;
			if (i >= 0)
				if (arr[i] == NULL)
					break ;
		}
	}
	return (arr);
}

static char		*ft_proper_path(char *path)
{
	int		m;
	int		n;
	char	**arr;
	char	*newpath;

	if (ft_strichr(path, '/') != -1)
	{
		m = (path[0] == '/') ? 1 : 0;
		n = (path[ft_strlen(path) - 1] == '/') ? 1 : 0;
		arr = ft_proper_path_2(path);
		newpath = ft_dbarrtostr(arr, '/');
		if (m == 1 && ft_strlen(newpath) > 0)
			newpath = ft_strinsert(newpath, '/', 0);
		if (n == 1)
			newpath = ft_strinsert(newpath, '/', ft_strlen(newpath));
		arr = ft_dbarr_free(arr);
		free(path);
		newpath = (ft_strcmp(newpath, "//") == 0) ?
		ft_strrem(newpath, 0) : newpath;
		return (newpath);
	}
	else
		return (path);
}

static char		*ft_cd_new_pwd(char *path)
{
	char	*tmp;
	char	*sav_path;

	if (path[0] != '/')
	{
		sav_path = ft_strdup(ft_path(0, NULL));
		if (sav_path[ft_strlen(sav_path) - 1] != '/')
			sav_path = ft_strjoinfree(sav_path, "/", 1);
		tmp = ft_strjoinfree(sav_path, path, 1);
	}
	else
		tmp = ft_strdup(path);
	if (tmp[ft_strlen(tmp) - 1] == '/' && ft_strlen(tmp) != 1)
		tmp = ft_strsubf(tmp, 0, ft_strlen(tmp) - 1);
	return ((tmp = ft_proper_path(tmp)));
}

static char		*ft_cd_check(char *tmp, char *path, int mode, char opt)
{
	if (opt == 'P')
	{
		free(tmp);
		tmp = getcwd(NULL, 0);
		chdir(tmp);
	}
	if (mode == 1 || mode == 2)
	{
		free(path);
		if (mode == 2)
			ft_putendl(tmp);
	}
	return (tmp);
}

int				ft_cd_path(char *path, char opt, int mode)
{
	char	*tmp;
	char	**new_env;

	tmp = ft_cd_new_pwd(path);
	if (access(tmp, F_OK) == -1)
		return (ft_cd_error(3, 0, path, tmp));
	else if (access(tmp, X_OK) == -1)
		return (ft_cd_error(4, 0, path, tmp));
	else if (is_dir(tmp) != 1)
		return (ft_cd_error(5, 0, path, tmp));
	else if (chdir(tmp) == -1)
		return (ft_cd_error(6, 0, path, tmp));
	else
	{
		tmp = ft_cd_check(tmp, path, mode, opt);
		ft_path(2, tmp);
		new_env = ft_change_pwd(ft_dbarrdup(ft_env(NULL, 0)), tmp);
		ft_env(new_env, 2);
		new_env = ft_dbarr_free(new_env);
		ft_strdel(&tmp);
		return (0);
	}
}
