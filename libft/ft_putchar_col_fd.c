/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_col_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swann <swann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:47:16 by swann             #+#    #+#             */
/*   Updated: 2018/03/08 13:47:19 by swann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_col_fd(char c, char *col, int fd)
{
	ft_putstr_fd(col, fd);
	write(fd, &c, 1);
	ft_putstr_fd(RESET, fd);
}
