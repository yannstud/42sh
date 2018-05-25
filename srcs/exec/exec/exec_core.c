/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 07:39:34 by amottier          #+#    #+#             */
/*   Updated: 2018/05/22 16:08:59 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		ft_exec_norme(int i)
{
	int		ret;

	if (WIFSIGNALED(i))
		ret = WTERMSIG(i) + 128;
	else
		ret = WEXITSTATUS(i);
	ft_pid(-1, 1);
	return (ret);
}

int				run_cmd(char *path, char **tabz, t_cmd *cmd, int to_fork)
{
	pid_t pid;

	if (!(check_cmd_syntax(tabz)))
		return (1);
	if (to_fork)
	{
		if ((pid = fork()) == -1)
			return (1);
		if (pid == 0)
		{
			execve(path, tabz, cmd->envir);
			exit(0);
		}
		ft_pid(pid, 1);
		waitpid(-1, &pid, WUNTRACED | WCONTINUED);
		if (!(WIFEXITED(pid)))
			return (ft_exec_norme(pid));
		ft_pid(-1, 1);
		return (WEXITSTATUS(pid));
	}
	else
		execve(path, tabz, cmd->envir);
	return (0);
}

int				not_bultin(char **tabz, t_cmd *cmd, int to_fork)
{
	char	*exec_path;
	int		retv;

	exec_path = NULL;
	retv = 1;
	exec_path = ft_getpath(tabz[0], cmd->envir);
	if (exec_path)
	{
		retv = run_cmd(exec_path, tabz, cmd, to_fork);
		ft_exit_value(1, retv);
		free(exec_path);
	}
	return (retv);
}
