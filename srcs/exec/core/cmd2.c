/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 15:59:46 by amottier          #+#    #+#             */
/*   Updated: 2018/05/23 17:42:37 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			check_backslash(char *str)
{
	int		i;
	int		bs;

	i = 0;
	bs = 0;
	while (str[i])
		i++;
	if (!(i))
		return (0);
	if (ft_strlen(str) == 1 && str[0] == '\\')
		return (1);
	while (i && str[i - 1] == '\\')
	{
		i--;
		bs++;
	}
	if (bs == 1)
		return (1);
	return (bs % 2);
}

int			last_is_oper(t_token *head, char *cmd)
{
	t_token *tmp;

	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp->type == TOKEN_BLANK || tmp->type == TOKEN_NEWLINE)
		tmp = tmp->prev;
	if (tmp->type == TOKEN_PIPE
		|| tmp->type == TOKEN_OR_IF
		|| tmp->type == TOKEN_AND_IF)
		return (3);
	else if ((cmd[ft_strlen(cmd) - 1] == '\\' && (check_backslash(cmd))))
		return (2);
	return (0);
}
