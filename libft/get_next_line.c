/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 02:39:28 by slegros           #+#    #+#             */
/*   Updated: 2017/12/12 04:34:18 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		gaule_melons(char **str, char **line)
{
	*line = ft_strdup(*str);
	ft_strdel(str);
}

static void		penetration_solide_mere(char **str, char **line)
{
	*line = ft_strsub(*str, 0, ft_strichr(*str, '\n'));
	*str = ft_strsubf(*str, ft_strichr(*str, '\n') + 1,
		ft_strlen(*str) - (ft_strichr(*str, '\n') + 1));
}

int				get_next_line(const int fd, char **line)
{
	int			ret;
	char		buf[BUFF_SIZE + 1];
	static char	*str;

	if ((int)fd < 0 || read(fd, buf, 0) < 0 || line == NULL)
		return (-1);
	if (!(str != NULL && ft_strichr(str, '\n') != -1))
	{
		if (!str)
			str = ft_strnew(0);
		while ((ret = read(fd, buf, BUFF_SIZE)))
		{
			buf[ret] = '\0';
			str = ft_strjoinfree(str, buf, 1);
			if (ft_strichr(buf, '\n') != -1)
				break ;
		}
		if (ret < BUFF_SIZE && str[0] == '\0')
			return (0);
	}
	if (str && ft_strichr(str, '\n') != -1)
		penetration_solide_mere(&str, line);
	else if (str && ft_strichr(str, '\n') == -1)
		gaule_melons(&str, line);
	return (1);
}
