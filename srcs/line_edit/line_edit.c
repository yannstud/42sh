/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:12:11 by slegros           #+#    #+#             */
/*   Updated: 2018/05/15 17:27:26 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		ft_line_noread(char *c)
{
	if (c[0] == 127 || c[0] == 21 || c[0] == 16 || c[0] == 11 || c[0] == 4
		|| c[0] == 9 || c[0] == 12)
	{
		if (c[0] == 21 || c[0] == 16 || c[0] == 11)
			ft_history(15, NULL, c[0]);
		else if (c[0] == 127)
			ft_history(8, NULL, 0);
		else if (c[0] == 4)
			ft_history(17, NULL, ft_button_line(0, 0));
		else if (c[0] == 9)
			ft_history(18, NULL, 0);
		else if (c[0] == 12)
			ft_history(14, NULL, 0);
		return (1);
	}
	return (0);
}

static void		ft_line(char *c)
{
	char	buf[3];

	if (ft_line_noread(c) == 1)
		return ;
	ft_bzero(buf, 3);
	read(0, buf, 3);
	if (c[0] == 27 && buf[0] == 91 && (buf[1] == 65 || buf[1] == 66)
		&& buf[2] == '\0')
		ft_history(4, NULL, (buf[1] * 2) - 131);
	else if (c[0] == 27 && buf[0] == 91 && (buf[1] == 67 || buf[1] == 68)
		&& buf[2] == '\0')
		ft_history(7, NULL, (buf[1] * 2) - 135);
	else if (c[0] == 27 && buf[0] == 91 && buf[1] == 51 && buf[2] == 126)
		ft_history(9, buf, 0);
	else if (c[0] == 27 && buf[0] == 91 && buf[2] == '\0'
		&& (buf[1] == 70 || buf[1] == 72))
		ft_history(11, NULL, buf[1] - 71);
	else if (c[0] == 27 && buf[0] == 27 && buf[1] == 91
		&& (buf[2] == 67 || buf[2] == 68))
		ft_history(12, NULL, (buf[2] * 2) - 135);
	else if (c[0] == 27 && buf[0] == 27 && buf[1] == 91
		&& (buf[2] == 65 || buf[2] == 66))
		ft_history(16, NULL, (buf[2] * 2) - 131);
}

static void		ft_set_line(char **line)
{
	t_h		tmp;

	ft_history(5, NULL, 0);
	tmp = ft_history(0, NULL, 0);
	ft_hist_return(tmp, 1);
	*line = ft_strdup(tmp.hist[ft_dbarrlen(tmp.hist) - 1]);
	if (ft_button_line(0, 0) == 2)
		ft_history(23, NULL, 0);
	if (ft_button_line(0, 0) == 4)
		ft_history(20, NULL, 0);
	ft_button_line(1, 1);
}

static void		ft_read_line_norme(int mode, t_cmd **cmd)
{
	if (mode == 1)
	{
		reset_cmd(cmd);
		ft_control_c(1, 0);
	}
	if (mode == 2)
	{
		if ((*cmd)->heredoc_mode == 1)
			(*cmd)->heredoc_done++;
		if ((*cmd)->heredoc_done == (*cmd)->heredoc_total)
			(*cmd)->heredoc_mode = 2;
	}
}

void			ft_read_line(char **line, t_cmd **cmd)
{
	char	buf[1];

	ft_history(2, NULL, 0);
	while (1)
	{
		ft_bzero(buf, 1);
		read(0, buf, 1);
		if (ft_control_c(0, 0) == 1)
			ft_read_line_norme(1, cmd);
		if (buf[0] >= 32 && buf[0] <= 126)
			ft_history(3, buf, 0);
		else
		{
			if (buf[0] == 10)
				break ;
			if (buf[0] == 4 && ft_button_line(0, 0) == 4 && nbl())
			{
				ft_read_line_norme(2, cmd);
				break ;
			}
			ft_line(buf);
		}
	}
	ft_set_line(line);
}
