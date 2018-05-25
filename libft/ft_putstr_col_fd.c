/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_col_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 12:06:49 by slegros           #+#    #+#             */
/*   Updated: 2018/02/15 12:06:52 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_col_fd(char *str, char *col, int fd)
{
	ft_putstr_fd(col, fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(RESET, fd);
}
