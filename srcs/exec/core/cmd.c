/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 13:35:38 by amottier          #+#    #+#             */
/*   Updated: 2018/05/22 16:00:16 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd			*init_cmd(void)
{
	t_cmd			*cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->command = NULL;
	cmd->debug = 0;
	cmd->give_me_more = 0;
	cmd->ast = NULL;
	cmd->head = NULL;
	cmd->heredoc = NULL;
	cmd->heredoc1 = NULL;
	cmd->heredoc_mode = 0;
	cmd->heredoc_total = 0;
	cmd->heredoc_done = 0;
	cmd->envir = ft_dbarrdup(ft_env(NULL, 0));
	get_fds();
	return (cmd);
}

t_cmd			*reset_cmd(t_cmd **cmd)
{
	free((*cmd)->command);
	if ((*cmd)->heredoc)
		free_heredoc((*cmd)->heredoc1);
	(*cmd)->command = NULL;
	(*cmd)->give_me_more = 0;
	(*cmd)->heredoc = NULL;
	(*cmd)->heredoc1 = NULL;
	(*cmd)->heredoc_mode = 0;
	(*cmd)->heredoc_total = 0;
	(*cmd)->heredoc_done = 0;
	(*cmd)->head = NULL;
	return (*cmd);
}

t_cmd			*insert_mode(char *line, t_cmd **cmd)
{
	if ((*cmd)->command == NULL)
		(*cmd)->command = ft_strdup(line);
	else if ((*cmd)->give_me_more == 2)
	{
		if ((*cmd)->command[ft_strlen((*cmd)->command) - 1] == '\\')
			(*cmd)->command[ft_strlen((*cmd)->command) - 1] = '\0';
		(*cmd)->command = ft_strjoinfree((*cmd)->command, line, 1);
	}
	else if ((*cmd)->give_me_more == 3)
	{
		(*cmd)->command = ft_strjoinfree((*cmd)->command, " ", 1);
		(*cmd)->command = ft_strjoinfree((*cmd)->command, line, 1);
	}
	else if (((*cmd)->give_me_more == 1
		|| !(gestion_quotes2((*cmd)->command))) &&
		!(((*cmd)->give_me_more == 1 && (gestion_quotes2((*cmd)->command)))))
	{
		(*cmd)->command = ft_strjoinfree((*cmd)->command, "\n", 1);
		(*cmd)->command = ft_strjoinfree((*cmd)->command, line, 1);
	}
	return (*cmd);
}

t_cmd			*heredoc_mode(char *line, t_cmd **cmd)
{
	t_heredoc	*hd;
	char		*tmp;

	hd = (*cmd)->heredoc;
	while (hd->next && (hd->position != (*cmd)->heredoc_done))
		hd = hd->next;
	if (!(ft_strcmp(line, hd->end_word)))
	{
		(*cmd)->heredoc_done++;
		if ((*cmd)->heredoc_done == (*cmd)->heredoc_total)
			(*cmd)->heredoc_mode = 2;
	}
	else if (!(hd->content))
		hd->content = ft_strdup(line);
	else
		hd->content = realloc_str(hd->content, line);
	if ((ft_strcmp(line, hd->end_word)))
	{
		tmp = ft_strjoin(hd->content, "\n");
		free(hd->content);
		hd->content = tmp;
	}
	return (*cmd);
}

t_cmd			*set_cmd(char *line, t_cmd **cmd)
{
	if (!(line))
		return (reset_cmd(cmd));
	if ((*cmd)->heredoc_mode != 1)
		insert_mode(line, cmd);
	else
		heredoc_mode(line, cmd);
	return (*cmd);
}
