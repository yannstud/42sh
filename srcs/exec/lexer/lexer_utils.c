/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 15:17:15 by amottier          #+#    #+#             */
/*   Updated: 2018/05/15 10:29:45 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			get_ascii_type(int c)
{
	if (c >= '0' && c <= '9')
		return (CHAR_DIGIT);
	else if (c == ' ' || c == '\t')
		return (CHAR_BLANK);
	else if (c == '\'')
		return (CHAR_SQUOTE);
	else if (c == '\"')
		return (CHAR_DQUOTE);
	else if (c == ';')
		return (CHAR_SEMICOLON);
	else if (c == '&')
		return (CHAR_AND);
	else if (c == '\n')
		return (CHAR_NEWLINE);
	else if (c == '<' || c == '>')
		return (CHAR_COMPARE);
	else if (c == '|')
		return (CHAR_PIPE);
	else if (c == '\\')
		return (CHAR_BACKSLASH);
	else
		return (CHAR_LETTER);
}

t_token		*new_elem(char *str, t_char_type type)
{
	t_token *elem;

	if (!(elem = malloc(sizeof(t_token))))
		return (NULL);
	elem->len = ft_strlen(str);
	elem->str = str;
	elem->type = type;
	elem->fd_from = -1;
	elem->fd_to = 1;
	elem->next = NULL;
	elem->prev = NULL;
	elem->filename = NULL;
	return (elem);
}

void		add_token(t_token **head, t_char_type type, char *str)
{
	t_token *tmp;
	t_token *elem;
	t_token *prev;

	prev = NULL;
	if (!(elem = new_elem(str, type)))
		return ;
	if (!(*head))
	{
		*head = elem;
		return ;
	}
	tmp = *head;
	prev = tmp;
	while (tmp->next)
	{
		tmp = tmp->next;
		prev = tmp;
	}
	elem->prev = prev;
	tmp->next = elem;
}

char		*crop_str(char *tmp, char *cmd, int start, int diff)
{
	return (ft_strsub(tmp, start,
		(ft_strlen(tmp) - ft_strlen(cmd) - start) + diff));
}

char		*process_backslash(char *s1)
{
	char	*p1;
	char	*p2;
	int		bs_pos;
	int		len;
	int		len_p1;

	bs_pos = ft_strnchr(s1, '\\', 0);
	len = ft_strlen(s1);
	while (bs_pos != -1)
	{
		p1 = ft_strsub(s1, 0, bs_pos);
		len_p1 = ft_strlen(p1) + 1;
		p2 = ft_strsub(s1, len_p1, len);
		free(s1);
		s1 = ft_strjoin(p1, p2);
		free(p1);
		free(p2);
		len = ft_strlen(s1);
		if (bs_pos < len)
			bs_pos = ft_strnchr(s1, '\\', len_p1);
		else
			bs_pos = -1;
	}
	return (s1);
}
