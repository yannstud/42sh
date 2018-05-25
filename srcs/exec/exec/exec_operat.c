/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 10:50:42 by amottier          #+#    #+#             */
/*   Updated: 2018/05/22 16:38:28 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		exec_semicolon(t_btree *ast, t_cmd *cmd)
{
	int ret;

	ret = 1;
	if (ast->left)
		exec_recursive(ast->left, 1, cmd);
	restore_fds();
	if (ast->right)
		ret = exec_recursive(ast->right, 1, cmd);
	return (ret);
}

int		exec_and(t_btree *ast, t_cmd *cmd)
{
	int		ret;

	ret = 1;
	if (!(exec_recursive(ast->left, 1, cmd)))
	{
		restore_fds();
		ret = exec_recursive(ast->right, 1, cmd);
	}
	return (ret);
}

int		exec_or(t_btree *ast, t_cmd *cmd)
{
	int		ret;

	ret = 0;
	if (exec_recursive(ast->left, 1, cmd) != 0)
	{
		restore_fds();
		ret = exec_recursive(ast->right, 1, cmd);
	}
	return (ret);
}

void	restore_exit(void)
{
	restore_fds();
	exit(0);
}

int		exec_pipe(t_btree *ast, t_cmd *cmd)
{
	int		link[2];
	pid_t	pid;
	int		ret;

	ret = 0;
	if (pipe(link) == -1 || ((pid = fork()) == -1) || ft_checks())
		return (1);
	if (pid == 0)
	{
		close(link[0]);
		dup2(link[1], STDOUT_FILENO);
		close(link[1]);
		ret = exec_recursive(ast->left, 0, cmd);
		restore_exit();
	}
	else
	{
		ft_close(link[1]);
		dup2(link[0], STDIN_FILENO);
		close(link[0]);
		ret = exec_recursive(ast->right, 1, cmd);
		restore_fds();
	}
	wait(NULL);
	return (ret);
}
