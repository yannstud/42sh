/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleto.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:44:35 by slegros           #+#    #+#             */
/*   Updated: 2018/05/16 17:13:50 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t		ft_pid(pid_t pid, int mode)
{
	static pid_t	save_pid;

	if (mode == 1)
		save_pid = pid;
	return (save_pid);
}

int			ft_control_c(int mode, int val)
{
	static int		sav_val;

	if (mode == 1)
		sav_val = val;
	return (sav_val);
}

t_wsize		ft_get_winsize(int mode)
{
	static t_wsize	w;

	if (mode == 1)
	{
		if (ioctl(0, TIOCGWINSZ, &w) == -1)
		{
			ft_putstr_col_fd("42sh: ", RED, 2);
			ft_putendl_col_fd("failed to get the terminal size", RED, 2);
			ft_term_reset();
			ft_history(6, NULL, 0);
			exit(EXIT_FAILURE);
		}
	}
	return (w);
}

int			ft_sigupk(int mode, int val)
{
	static int	sav_val;

	if (mode == 1)
		sav_val = val;
	return (sav_val);
}

char		*ft_create_line(char *line, char *tmp)
{
	if (ft_strnoreadable(line) == 0)
	{
		tmp = ft_strjoinfree(tmp, line, 3);
		tmp = ft_strjoinfree(tmp, "\n", 1);
	}
	else
		free(line);
	return (tmp);
}
