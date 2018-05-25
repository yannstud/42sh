/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inbrk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swann <swann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 13:13:51 by swann             #+#    #+#             */
/*   Updated: 2018/04/06 13:18:38 by swann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_brk	ft_init_brk(void)
{
	t_brk	b;

	b.cursh = 0;
	b.subsh = 0;
	b.quote = 0;
	b.dquote = 0;
	b.bquote = 0;
	return (b);
}

static int		ft_checkbrk(t_brk b)
{
	if (b.cursh > 0 || b.subsh > 0 || b.quote > 0
		|| b.dquote > 0 || b.bquote > 0)
	{
		return (1);
	}
	else
		return (0);
}

int				ft_inbrk(char *str, int index)
{
	t_brk	b;
	int		i;

	b = ft_init_brk();
	i = 0;
	while (str[i] != '\0' && i < index)
	{
		if (str[i] == '(' && b.quote == 0 && b.dquote == 0 && b.bquote == 0)
			b.cursh++;
		if (str[i] == ')' && b.quote == 0 && b.dquote == 0 && b.bquote == 0)
			b.cursh--;
		if (str[i] == '{' && b.quote == 0 && b.dquote == 0 && b.bquote == 0)
			b.subsh++;
		if (str[i] == '}' && b.quote == 0 && b.dquote == 0 && b.bquote == 0)
			b.subsh--;
		if (str[i] == 39 && b.dquote == 0 && b.bquote == 0)
			b.quote = (b.quote == 0) ? 1 : 0;
		if (str[i] == 34 && b.quote == 0 && b.bquote == 0)
			b.dquote = (b.dquote == 0) ? 1 : 0;
		if (str[i] == 96)
			b.bquote = (b.bquote == 0) ? 1 : 0;
		i += (str[i] == 92) ? 1 : 0;
		i++;
	}
	return (ft_checkbrk(b));
}
