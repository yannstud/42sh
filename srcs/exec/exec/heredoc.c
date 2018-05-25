/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:29:36 by ysalaun           #+#    #+#             */
/*   Updated: 2018/05/22 15:53:14 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		add_heredoc(t_cmd **cmd, int pos, char *end_word)
{
	t_heredoc *hd;
	t_heredoc *new_hd;

	new_hd = malloc(sizeof(t_heredoc));
	new_hd->position = pos;
	new_hd->end_word = ft_strdup(end_word);
	new_hd->content = NULL;
	new_hd->next = NULL;
	hd = (*cmd)->heredoc;
	if (!(hd))
	{
		(*cmd)->heredoc = new_hd;
		(*cmd)->heredoc1 = new_hd;
	}
	else
	{
		while (hd->next)
			hd = hd->next;
		hd->next = new_hd;
	}
	(*cmd)->heredoc_total++;
}

int			parse_heredoc(t_cmd **cmd)
{
	t_token	*tmp;
	char	*end_word;
	int		pos;

	pos = 0;
	tmp = (*cmd)->head;
	while (tmp->next)
	{
		if (tmp->type == TOKEN_DLESS)
		{
			tmp = tmp->next;
			while (tmp->type == TOKEN_BLANK)
				tmp = tmp->next;
			end_word = tmp->str;
			add_heredoc(cmd, pos, end_word);
			pos++;
		}
		if (tmp->next)
			tmp = tmp->next;
	}
	if (!(pos))
		(*cmd)->heredoc_mode = 2;
	return (pos);
}
