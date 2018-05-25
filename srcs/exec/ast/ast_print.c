/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 09:28:05 by amottier          #+#    #+#             */
/*   Updated: 2018/05/10 14:05:27 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		print_childs(t_btree *ast)
{
	t_token *tkn;

	tkn = ast->data;
	ft_putchar('(');
	ft_putstr(ast->parent->data->str);
	ft_putstr(") -> (");
	while (tkn)
	{
		ft_putstr(tkn->str);
		tkn = tkn->next;
	}
	ft_putendl(")");
}

void			print_tree_prefix(t_btree *ast)
{
	if (ast == NULL)
		return ;
	if (ast->parent != NULL)
	{
		print_childs(ast);
	}
	else
	{
		ft_putchar('(');
		ft_putstr(ast->data->str);
		ft_putendl(")");
	}
	if (ast->left != NULL)
		print_tree_prefix(ast->left);
	if (ast->right != NULL)
		print_tree_prefix(ast->right);
}
