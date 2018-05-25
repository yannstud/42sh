/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 11:33:44 by amottier          #+#    #+#             */
/*   Updated: 2018/05/22 16:38:43 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			open_file(char *filename, int append, int read)
{
	int fd;

	if (read)
		fd = open(filename, O_RDONLY);
	else if (append)
		fd = open(filename, O_WRONLY | O_APPEND
			| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd = open(filename, O_WRONLY | O_TRUNC
			| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		if (access(filename, F_OK) == -1)
			err_no_file(filename);
		else if ((!read && access(filename, W_OK) != 0)
			|| (read && access(filename, R_OK) != 0))
			err_no_file_perm(filename);
	}
	return (fd);
}

int			check_cmd_syntax(char **tabz)
{
	if (tabz[0] && ft_strlen(tabz[0]) == 0)
	{
		ft_putstr_col_fd("42sh: Command not found: ", YEL, 2);
		ft_putendl_col_fd("", YEL, 2);
		ft_exit_value(1, 127);
		return (0);
	}
	if (!tabz[0] || !(ft_strcmp(tabz[0], ".")) || !(ft_strcmp(tabz[0], "..")))
		return (0);
	else
		return (1);
}

void		ft_close(int lnk)
{
	int i;

	i = 0;
	close(lnk);
	while (i < 1000000)
		i++;
}

int			ft_checks(void)
{
	int i;

	i = 0;
	while (i < 1000000)
		i++;
	return (0);
}
