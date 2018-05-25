/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 15:17:15 by amottier          #+#    #+#             */
/*   Updated: 2018/05/14 13:27:17 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pipe(char **cmd, t_token **head)
{
	char *str;

	str = *cmd;
	if (**cmd && *(str + 1) == '|')
	{
		add_token(head, TOKEN_OR_IF, ft_strdup("||"));
		(*cmd)++;
	}
	else
		add_token(head, TOKEN_PIPE, ft_strdup("|"));
	(*cmd)++;
}

void	handle_and(char **cmd, t_token **head)
{
	char *str;

	str = *cmd;
	if (**cmd && *(str + 1) == '&')
	{
		add_token(head, TOKEN_AND_IF, ft_strdup("&&"));
		(*cmd)++;
	}
	else if (**cmd && *(str + 1) == '>')
	{
		add_token(head, TOKEN_ANDGREAT, ft_strdup("&>"));
		(*cmd)++;
	}
	else
	{
		add_token(head, TOKEN_AND, ft_strdup("&"));
	}
	(*cmd)++;
}

int		ft_strnchr(const char *str, int c, int start)
{
	int	i;

	i = start;
	while (str[i])
	{
		if ((char)c == str[i])
		{
			return (i);
		}
		i++;
	}
	if ((char)c == '\0')
		return (-1);
	return (-1);
}

void	handle_word(char **cmd, t_token **head, char *tmp, int start)
{
	char	*s1;
	int		escaped;

	escaped = 0;
	while (**cmd && (get_ascii_type(**cmd) == CHAR_LETTER
				|| get_ascii_type(**cmd) == CHAR_DIGIT
				|| (escaped)
				|| (get_ascii_type(**cmd) == CHAR_BACKSLASH)))
	{
		escaped = 0;
		if (get_ascii_type(**cmd) == CHAR_BACKSLASH)
			escaped = 1;
		(*cmd)++;
	}
	s1 = process_backslash(crop_str(tmp, *cmd, start, 0));
	add_token(head, TOKEN_WORD, s1);
}

void	handle_digit(char **cmd, t_token **head, char *tmp, int start)
{
	int letter;

	letter = 0;
	while (**cmd && ((get_ascii_type(**cmd) == CHAR_LETTER
				|| get_ascii_type(**cmd) == CHAR_DIGIT)))
	{
		if (get_ascii_type(**cmd) == CHAR_LETTER)
			letter++;
		(*cmd)++;
	}
	if (!(letter))
		add_token(head, TOKEN_IO_NUMBER, crop_str(tmp, *cmd, start, 0));
	else
		add_token(head, TOKEN_WORD, crop_str(tmp, *cmd, start, 0));
}
