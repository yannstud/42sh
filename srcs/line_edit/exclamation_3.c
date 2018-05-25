/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swann <swann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 17:05:14 by slegros           #+#    #+#             */
/*   Updated: 2018/05/22 20:07:42 by swann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_exclam_error(char *tmp, char *str, int mode)
{
	ft_putstr_col_fd("42sh: Event not found: !", YEL, 2);
	if (mode == 2 || mode == 5)
		ft_putstr_col_fd("?", YEL, 2);
	ft_putstr_col_fd(tmp, YEL, 2);
	if (mode == 5)
		ft_putstr_col_fd("?", YEL, 2);
	else
		ft_putchar_col_fd('\n', YEL, 2);
	ft_history(20, NULL, 0);
	str[0] = '\0';
	free(tmp);
	return (str);
}

char	*ft_excla_replace(char *str, char *new, int start, int end)
{
	char	*tmp;

	tmp = ft_strsub(str, end, ft_strlen(str) - end);
	str = ft_strsubf(str, 0, start);
	str = ft_strjoinfree(str, new, 1);
	str = ft_strjoinfree(str, tmp, 3);
	return (str);
}
