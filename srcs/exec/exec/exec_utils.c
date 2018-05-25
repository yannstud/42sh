/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 11:25:58 by amottier          #+#    #+#             */
/*   Updated: 2018/05/10 14:05:21 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_both(int fd)
{
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
}

int		exec_write_and_closed(t_btree *ast, int to_fork, t_cmd *cmd)
{
	if (ast->data->fd_from == -1)
	{
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	else
		close(ast->data->fd_from);
	return (exec_recursive(ast->left, to_fork, cmd));
}
