/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 10:44:15 by amottier          #+#    #+#             */
/*   Updated: 2018/05/19 15:12:12 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		exec_read_and(t_btree *ast, int to_fork, t_cmd *cmd)
{
	int		fd;
	int		ret;
	int		fd_tmp;

	if (ast->data->filename)
	{
		if ((fd = open_file(ast->data->filename, 0, 1)) == -1)
			return (0);
	}
	else
	{
		fd = ast->data->fd_to;
		if ((fd_tmp = dup(fd)) == -1)
			return (err_no_fd(fd));
		close(fd_tmp);
	}
	if (ast->data->fd_from == -1)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, ast->data->fd_from);
	ret = exec_recursive(ast->left, to_fork, cmd);
	close(fd);
	return (ret);
}

int		exec_read(t_btree *ast, int to_fork, t_cmd *cmd)
{
	int		fd;
	int		ret;

	if ((fd = open_file(ast->data->filename, 0, 1)) == -1)
		return (0);
	if (ast->data->fd_from == -1)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, ast->data->fd_from);
	ret = exec_recursive(ast->left, to_fork, cmd);
	close(fd);
	return (ret);
}

int		exec_heredoc(t_btree *ast, int to_fork, t_cmd *cmd)
{
	int		ret;
	int		fd;

	fd = open("/tmp/.heredoc2", O_WRONLY | O_TRUNC
			| O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	ft_putstr_fd(cmd->heredoc->content, fd);
	if (cmd->heredoc->next)
		cmd->heredoc = cmd->heredoc->next;
	if ((fd = open("/tmp/.heredoc2", O_RDONLY)) == -1)
		return (err_no_file(".heredoc2"));
	dup2(fd, STDIN_FILENO);
	ret = exec_recursive(ast->left, to_fork, cmd);
	close(fd);
	return (ret);
}
