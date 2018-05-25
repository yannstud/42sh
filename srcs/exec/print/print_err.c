/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 14:08:25 by amottier          #+#    #+#             */
/*   Updated: 2018/05/12 15:22:06 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		print_err(char *name, int type)
{
	if (type == 1)
	{
		ft_putstr_col_fd("42sh: ", YEL, 2);
		ft_putstr_col_fd(name, YEL, 2);
		ft_putstr_col_fd(": command not found\n", YEL, 2);
	}
}

void		print_err_cd(int stat_res, char *path, struct stat path_stat)
{
	if (stat_res == -1)
	{
		ft_putstr_col_fd("42sh: ", YEL, 2);
		ft_putstr_col_fd("cd: no such file or directory: ", YEL, 2);
	}
	else if (S_ISREG(path_stat.st_mode))
	{
		ft_putstr_col_fd("42sh: ", YEL, 2);
		ft_putstr_col_fd("cd: not a directory: ", YEL, 2);
	}
	else if (!(path_stat.st_mode & S_IRUSR))
	{
		ft_putstr_col_fd("42sh: ", YEL, 2);
		ft_putstr_col_fd("cd: permission denied: ", YEL, 2);
	}
	ft_putendl_col_fd(path, YEL, 2);
}

int			err_no_file(char *msg)
{
	ft_putstr_col_fd("42sh: no such file or directory: ", YEL, 2);
	ft_putendl_col_fd(msg, YEL, 2);
	return (1);
}

int			err_no_fd(int fd_nbr)
{
	ft_putstr_col_fd("42sh: ", YEL, 2);
	ft_putnbr_col_fd(fd_nbr, YEL, 2);
	ft_putendl_col_fd(": bad file descriptor", YEL, 2);
	return (1);
}

void		err_no_cmd(char *cmd)
{
	ft_putstr_col_fd("42sh: ", YEL, 2);
	ft_putstr_col_fd(cmd, YEL, 2);
	ft_putendl_col_fd(": Command not found", YEL, 2);
}
