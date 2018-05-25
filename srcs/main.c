/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swann <swann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:35:34 by slegros           #+#    #+#             */
/*   Updated: 2018/05/22 13:41:14 by swann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_launchshell(void)
{
	char	*line;
	t_cmd	*cmd;

	if (!(cmd = init_cmd()))
		return ;
	while (42)
	{
		ft_putstr_col_fd(ft_where(0, NULL), BOLD, 0);
		line = ft_get_entry(&cmd);
		if (line != NULL)
		{
			enter(line, &cmd);
			free(line);
		}
	}
}

int			main(void)
{
	char			**env;

	env = ft_get_env();
	ft_env(env, 1);
	ft_term_check(env);
	ft_term(3);
	ft_term(2);
	ft_term(1);
	ft_get_winsize(1);
	ft_history(1, NULL, 0);
	ft_welcome(env);
	ft_where(1, NULL);
	ft_signal();
	ft_path(1, NULL);
	ft_button_line(1, 1);
	ft_control_c(1, 0);
	ft_sigupk(1, 0);
	ft_launchshell();
	return (0);
}
