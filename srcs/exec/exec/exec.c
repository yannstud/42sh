/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 10:16:06 by amottier          #+#    #+#             */
/*   Updated: 2018/05/22 15:51:19 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			**tabz_pocess(t_token *tkn, int i)
{
	char	**tabz;

	if (!(tabz = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (tkn)
	{
		if (tkn->type != TOKEN_BLANK && tkn->type != TOKEN_SEMI)
		{
			if (tkn->type == TOKEN_DQUOTE || tkn->type == TOKEN_SQUOTE)
			{
				if (ft_strlen(tkn->str) > 2)
					tabz[i] = ft_strsub(tkn->str, 1, ft_strlen(tkn->str) - 2);
				else
					tabz[i] = ft_strdup("");
			}
			else
				tabz[i] = ft_strdup(tkn->str);
			i++;
		}
		tkn = tkn->next;
	}
	tabz[i] = NULL;
	return (tabz);
}

char			**tabz_from_token(t_token *tkn)
{
	int			i;
	t_token		*tmp;

	i = 0;
	tmp = tkn;
	while (tmp)
	{
		if (tmp->type != TOKEN_BLANK)
			i++;
		tmp = tmp->next;
	}
	if (!(i))
		return (NULL);
	return (tabz_pocess(tkn, i));
}

int				exec(char **tabz, int to_fork, t_cmd *cmd)
{
	int		ret;

	if (!(tabz[0]))
		return (0);
	if (ft_strcmp(tabz[0], "echo") == 0)
		return (ft_exec_echo(tabz));
	else if (ft_strcmp(tabz[0], "exit") == 0
		|| ft_strcmp(tabz[0], "history") == 0
		|| ft_strcmp(tabz[0], "setenv") == 0
		|| ft_strcmp(tabz[0], "unsetenv") == 0
		|| ft_strcmp(tabz[0], "env") == 0
		|| ft_strcmp(tabz[0], "cd") == 0)
	{
		ret = ft_launch_builtin(tabz, cmd->envir, cmd);
		cmd->envir = ft_dbarr_free(cmd->envir);
		cmd->envir = ft_dbarrdup(ft_env(NULL, 0));
		return (ret);
	}
	else
		return (not_bultin(tabz, cmd, to_fork));
}

int				start_exec(t_btree *ast, int to_fork, t_cmd *cmd)
{
	int		res;
	char	**tabz;

	if (!(tabz = tabz_from_token(ast->data)))
		return (0);
	res = exec(tabz, to_fork, cmd);
	free_tabz(tabz);
	return (res);
}

int				exec_recursive(t_btree *ast, int to_fork, t_cmd *cmd)
{
	if (!(ast))
		return (0);
	if (ast->data->type == TOKEN_SEMI)
		return (exec_semicolon(ast, cmd));
	else if (ast->data->type == TOKEN_AND_IF)
		return (exec_and(ast, cmd));
	else if (ast->data->type == TOKEN_OR_IF)
		return (exec_or(ast, cmd));
	else if (ast->data->type == TOKEN_PIPE)
		return (exec_pipe(ast, cmd));
	else if (ast->data->type == TOKEN_GREAT || ast->data->type == TOKEN_DGREAT)
		return (exec_write(ast, to_fork, cmd));
	else if (ast->data->type == TOKEN_ANDGREAT)
		return (exec_andwrite(ast, to_fork, cmd));
	else if (ast->data->type == TOKEN_LESSAND)
		return (exec_read_and(ast, to_fork, cmd));
	else if (ast->data->type == TOKEN_GREATAND)
		return (exec_write_and(ast, to_fork, cmd));
	else if (ast->data->type == TOKEN_LESS)
		return (exec_read(ast, to_fork, cmd));
	else if (ast->data->type == TOKEN_DLESS)
		return (exec_heredoc(ast, to_fork, cmd));
	else
		return (start_exec(ast, to_fork, cmd));
}
