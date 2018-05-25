/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:28:13 by slegros           #+#    #+#             */
/*   Updated: 2018/05/22 16:04:34 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		launch_exec(t_cmd **cmd)
{
	int ret;

	ft_term_reset();
	(*cmd)->ast = create_ast((*cmd)->head);
	if ((*cmd)->debug)
		print_tree_prefix((*cmd)->ast);
	ret = exec_recursive((*cmd)->ast, 1, *cmd);
	clean_tree((*cmd)->ast);
	set_cmd(NULL, cmd);
	restore_fds();
	ft_term(1);
}

void		parsing_ok(t_cmd **cmd)
{
	int tmp;

	if (gestion_quotes2((*cmd)->command))
	{
		if ((tmp = last_is_oper((*cmd)->head, (*cmd)->command)))
			(*cmd)->give_me_more = tmp;
		else if ((!(*cmd)->heredoc_mode) && parse_heredoc(cmd))
		{
			(*cmd)->heredoc_mode = 1;
			(*cmd)->give_me_more = 1;
		}
		else if ((*cmd)->heredoc_mode == 2)
			launch_exec(cmd);
	}
	else
		(*cmd)->give_me_more = 1;
}

void		end_enter(t_cmd **cmd)
{
	if (!((*cmd)->give_me_more))
	{
		ft_button_line(1, 1);
		ft_where(2, NULL);
		ft_where(1, NULL);
	}
	else
	{
		ft_where(2, NULL);
		if ((*cmd)->heredoc_mode == 1)
		{
			ft_where(3, "heredoc> ");
			ft_button_line(1, 4);
		}
		else
		{
			ft_button_line(1, 2);
			ft_where(3, "> ");
		}
	}
}

void		enter(char *line, t_cmd **cmd)
{
	if (has_line(line) || (*cmd)->heredoc_mode == 2 || (*cmd)->give_me_more)
	{
		set_cmd(line, cmd);
		get_token(&(*cmd)->head, (*cmd)->command);
		if ((*cmd)->debug == 1)
			print_tokens((*cmd)->head);
		if (parsing((*cmd)->head))
			parsing_ok(cmd);
		else
		{
			free_token((*cmd)->head);
			set_cmd(NULL, cmd);
		}
		free_token((*cmd)->head);
	}
	(*cmd)->head = NULL;
	end_enter(cmd);
}
