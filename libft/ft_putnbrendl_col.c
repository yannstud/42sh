/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrendl_col.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 12:07:13 by slegros           #+#    #+#             */
/*   Updated: 2018/02/15 12:07:14 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbrendl_col(int nb, char *col)
{
	ft_putstr(col);
	ft_putnbr(nb);
	ft_putendl(RESET);
}
