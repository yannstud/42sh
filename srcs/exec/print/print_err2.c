/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 14:08:25 by amottier          #+#    #+#             */
/*   Updated: 2018/05/14 14:13:43 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		parsing_error(char *str)
{
	ft_putstr_col_fd("42sh: parse error near `", YEL, 2);
	ft_putstr_col_fd(str, YEL, 2);
	ft_putendl_col_fd("'", YEL, 2);
	ft_exit_value(1, 258);
}

int			err_no_file_perm(char *msg)
{
	ft_putstr_col_fd("42sh: ", YEL, 2);
	ft_putstr_col_fd(msg, YEL, 2);
	ft_putendl_col_fd(": Permission denied", YEL, 2);
	return (1);
}
