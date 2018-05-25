/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 15:17:15 by amottier          #+#    #+#             */
/*   Updated: 2018/05/10 14:05:18 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_compare_great(char **cmd, t_token **head)
{
	char	*str;

	str = *cmd;
	if (*(str + 1) == '>')
	{
		add_token(head, TOKEN_DGREAT, ft_strdup(">>"));
		(*cmd)++;
	}
	else if (*(str + 1) == '&')
	{
		add_token(head, TOKEN_GREATAND, ft_strdup(">&"));
		(*cmd)++;
	}
	else if (*(str + 1) == '<')
	{
		add_token(head, TOKEN_LESSGREAT, ft_strdup("><"));
		(*cmd)++;
	}
	else
		add_token(head, TOKEN_GREAT, ft_strdup(">"));
	(*cmd)++;
}

void	handle_compare_less(char **cmd, t_token **head)
{
	char	*str;

	str = *cmd;
	if (*(str + 1) == '<')
	{
		add_token(head, TOKEN_DLESS, ft_strdup("<<"));
		(*cmd)++;
	}
	else if (*(str + 1) == '&')
	{
		add_token(head, TOKEN_LESSAND, ft_strdup("<&"));
		(*cmd)++;
	}
	else if (*(str + 1) == '>')
	{
		add_token(head, TOKEN_LESSGREAT, ft_strdup("<>"));
		(*cmd)++;
	}
	else
		add_token(head, TOKEN_LESS, ft_strdup("<"));
	(*cmd)++;
}
