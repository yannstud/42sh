/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 06:11:09 by slegros           #+#    #+#             */
/*   Updated: 2018/05/15 17:23:36 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		*ft_where_buf(char *buf)
{
	buf = ft_strsubf(buf, 3, ft_strlen(buf) - 3);
	buf[0] = 'e';
	buf[ft_strichr(buf, '.')] = 'r';
	buf[ft_strichr(buf, '.')] = 'p';
	buf = ft_strjoinfree(buf, "> ", 1);
	return (buf);
}

char			*ft_where(int mode, char *str)
{
	int				fd;
	struct ifreq	ifr;
	static char		*buf;

	if (mode == 1)
	{
		fd = socket(AF_INET, SOCK_DGRAM, 0);
		ifr.ifr_addr.sa_family = AF_INET;
		ft_strncpy(ifr.ifr_name, "en0", IFNAMSIZ - 1);
		ioctl(fd, SIOCGIFADDR, &ifr);
		close(fd);
		buf = ft_strdup(inet_ntoa(((t_sockad *)&ifr.ifr_addr)->sin_addr));
		if (ft_strncmp(buf, "10", 2) != 0)
		{
			free(buf);
			buf = ft_strdup("$> ");
		}
		else
			buf = ft_where_buf(buf);
	}
	else if (mode == 2)
		free(buf);
	else if (mode == 3)
		buf = ft_strdup(str);
	return (buf);
}

void			ft_hello_bye(char *col)
{
	t_wsize		w;
	int			i;

	w = ft_get_winsize(0);
	i = 0;
	if ((w.ws_col - 8) % 2 == 1)
		ft_putstr_col_fd("–", col, 0);
	while (i < (w.ws_col - 8) / 2)
	{
		ft_putstr_col_fd("–", col, 0);
		i++;
	}
	ft_putstr_col_fd("[ 42sh ]", col, 0);
	i = 0;
	while (i < (w.ws_col - 8) / 2)
	{
		ft_putstr_col_fd("–", col, 0);
		i++;
	}
	ft_putchar_fd('\n', 0);
}

void			ft_welcome(char **env)
{
	time_t		today;
	char		*tmp2;

	ft_putstr_fd(tgetstr("cl", NULL), 0);
	ft_hello_bye(BGRN);
	tmp2 = ft_get_elem(env, "USER");
	today = time(0);
	ft_putstr(ctime(&today));
	ft_putstr("Welcome on 42sh, ");
	if (tmp2 != NULL)
	{
		ft_putstr(tmp2);
		ft_putendl(".");
		ft_strdel(&tmp2);
	}
	else
		ft_putendl("bro.");
}
