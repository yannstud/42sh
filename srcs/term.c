/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swann <swann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 20:30:43 by slegros           #+#    #+#             */
/*   Updated: 2018/05/22 13:41:46 by swann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			ft_term_check(char **env)
{
	char	*env_term;

	if ((env_term = ft_get_elem(env, "TERM")) == NULL)
	{
		ft_putendl_col_fd("42sh: TERM not set in the environnement", RED, 2);
		free(env_term);
		exit(EXIT_FAILURE);
	}
	if (tgetent(NULL, env_term) < 1)
	{
		ft_putendl_col_fd("42sh: failed to load terminfo database", RED, 2);
		free(env_term);
		exit(EXIT_FAILURE);
	}
	free(env_term);
}

static void		ft_term_error(char *err)
{
	ft_putstr_col_fd("42sh: failed to ", RED, 2);
	ft_putstr_col_fd(err, RED, 2);
	ft_putendl_col_fd(" terminal's attributes", RED, 2);
	exit(EXIT_FAILURE);
}

static void		ft_term_init(struct termios *term_attr)
{
	term_attr->c_lflag &= ~(ICANON);
	term_attr->c_lflag &= ~(ECHO);
	term_attr->c_cc[VMIN] = 1;
	term_attr->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term_attr) == -1)
		ft_term_error("set");
}

struct termios	ft_term(int mode)
{
	static struct termios	term_attr;
	static struct termios	term_attr_save;

	if (mode == 1)
		ft_term_init(&term_attr);
	if (mode == 2)
	{
		if (tcgetattr(0, &term_attr) == -1)
			ft_term_error("store");
	}
	if (mode == 3)
	{
		if (tcgetattr(0, &term_attr_save) == -1)
			ft_term_error("store");
	}
	if (mode == 4)
		return (term_attr_save);
	return (term_attr);
}

void			ft_term_reset(void)
{
	struct termios	term_attr;

	term_attr = ft_term(4);
	if (tcsetattr(0, TCSADRAIN, &term_attr) == -1)
		exit(EXIT_FAILURE);
}
