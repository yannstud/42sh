/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 18:00:50 by amottier          #+#    #+#             */
/*   Updated: 2018/05/19 14:21:50 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			test(t_qots *b, char c, int *i, char *cmd)
{
	if (c == '[' && b->qu == 0 && b->dqu == 0 && b->bqu == 0)
		b->crosh++;
	if (c == ']' && b->qu == 0 && b->dqu == 0 && b->bqu == 0)
		b->crosh--;
	if (c == '{' && b->qu == 0 && b->dqu == 0 && b->bqu == 0)
		b->cursh++;
	if (c == '}' && b->qu == 0 && b->dqu == 0 && b->bqu == 0)
		b->cursh--;
	if (c == '(' && b->qu == 0 && b->dqu == 0 && b->bqu == 0)
		b->subsh++;
	if (c == ')' && b->qu == 0 && b->dqu == 0 && b->bqu == 0)
		b->subsh--;
	if (c == 39 && b->dqu == 0 && b->bqu == 0)
		b->qu = (b->qu == 0) ? 1 : 0;
	if (c == 34 && b->qu == 0 && b->bqu == 0)
		b->dqu = (b->dqu == 0) ? 1 : 0;
	if (c == 96 && b->qu == 0 && b->dqu == 0)
		b->bqu = (b->bqu == 0) ? 1 : 0;
	if (cmd[*i + 1] && c == '\\')
		(*i)++;
}

int				gestion_quotes2(char *cmd)
{
	int		i;
	t_qots	b;

	i = -1;
	b.qu = 0;
	b.dqu = 0;
	b.bqu = 0;
	b.cursh = 0;
	b.subsh = 0;
	b.crosh = 0;
	while (cmd[++i])
	{
		test(&b, cmd[i], &i, cmd);
	}
	return (b.qu <= 0 && b.dqu <= 0 && b.bqu <= 0
			&& b.subsh <= 0 && b.cursh <= 0 && b.crosh <= 0);
}

int				check_unsopprted_tokens(t_token *head)
{
	t_token *tmp;

	tmp = head;
	if (!(tmp))
		return (0);
	while (tmp)
	{
		if (tmp->type == TOKEN_AND)
		{
			parsing_error(tmp->str);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
