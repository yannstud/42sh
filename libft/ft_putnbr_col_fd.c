/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_col_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 12:07:26 by slegros           #+#    #+#             */
/*   Updated: 2018/02/15 12:07:27 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_col_fd(int nb, char *col, int fd)
{
	ft_putstr_fd(col, fd);
	ft_putnbr_fd(nb, fd);
	ft_putstr_fd(RESET, fd);
}
