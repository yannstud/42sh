/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_tools_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 16:12:17 by slegros           #+#    #+#             */
/*   Updated: 2018/05/15 15:13:19 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**ft_mystrsplit(char *str, char c, int nb)
{
	char	**array;
	int		i;
	char	*tmp;

	tmp = ft_strdup(str);
	i = 0;
	if (!(array = (char **)malloc(sizeof(char *) * (nb + 1))))
		return (NULL);
	while (i < nb)
	{
		array[i] = ft_strsub(tmp, 0, ft_strichr(tmp, c));
		tmp = ft_strsubf(tmp, ft_strichr(tmp, c) + 1,
			ft_strlen(tmp) - (ft_strichr(tmp, c) + 1));
		i++;
	}
	ft_strdel(&tmp);
	array[i] = NULL;
	return (array);
}

char		**ft_dbarr_dir(char *dir, char *file, int mode)
{
	DIR				*dir_flx;
	char			*tmp;
	struct dirent	*infos;
	char			**names;
	int				i;

	dir_flx = opendir(dir);
	if (dir_flx == NULL)
		return (NULL);
	tmp = ft_strnew(0);
	i = 0;
	while ((infos = readdir(dir_flx)))
	{
		if ((mode == 1 && ft_strncmp(infos->d_name, file,
			ft_strlen(file)) == 0) || mode == 2)
		{
			tmp = ft_strjoinfree(tmp, infos->d_name, 1);
			tmp = ft_strjoinfree(tmp, "/", 1);
			i++;
		}
	}
	names = ft_mystrsplit(tmp, '/', i);
	ft_strdel(&tmp);
	closedir(dir_flx);
	return (names);
}

t_grl		ft_get_nb(char **ar_list, struct winsize w)
{
	t_grl			nb;
	int				i;
	int				maxcol;

	i = -1;
	nb.max_len = 0;
	while (ar_list[++i] != NULL)
	{
		if (ft_strlen(ar_list[i]) > nb.max_len)
			nb.max_len = ft_strlen(ar_list[i]);
	}
	nb.row = 0;
	nb.col = 1;
	nb.ar_len = ft_dbarrlen(ar_list);
	maxcol = 1;
	if ((w.ws_col / (nb.max_len + 1)) > 0)
		maxcol = w.ws_col / (nb.max_len + 1);
	while (nb.col * nb.row < nb.ar_len)
	{
		nb.row++;
		nb.col = 1;
		while (nb.col * nb.row < nb.ar_len && nb.col < maxcol)
			nb.col++;
	}
	return (nb);
}

void		ft_print_space(int max_len, int len_elem)
{
	while (len_elem <= max_len)
	{
		ft_putchar_fd(' ', 0);
		len_elem++;
	}
}

char		**ft_proper_list(char **list)
{
	int		i;
	int		j;

	i = -1;
	while (list[++i] != NULL)
	{
		j = -1;
		while (list[i][++j] != '\0')
		{
			if (list[i][j] < 32 || list[i][j] > 126)
				list[i][j] = '?';
		}
	}
	return (list);
}
