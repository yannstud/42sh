/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbarrprint_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 12:09:15 by slegros           #+#    #+#             */
/*   Updated: 2018/02/15 12:09:18 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dbarrprint_fd(char **dbarr, int fd)
{
	int		i;

	i = 0;
	while (dbarr[i] != NULL)
	{
		ft_putendl_fd(dbarr[i], fd);
		i++;
	}
}
