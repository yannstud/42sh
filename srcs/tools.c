/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swann <swann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 09:12:51 by slegros           #+#    #+#             */
/*   Updated: 2018/05/22 20:05:30 by swann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_get_elem(char **env, char *elem)
{
	char	*cont_elem;
	int		i;

	i = 0;
	cont_elem = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], elem, ft_strlen(elem)) == 0
			&& env[i][ft_strlen(elem)] == '=')
		{
			cont_elem = ft_strsub(env[i], ft_strlen(elem) + 1,
				ft_strlen(env[i]) - (ft_strlen(elem) + 1));
		}
		i++;
	}
	return (cont_elem);
}

int			ft_get_elemi(char **env, char *elem)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], elem, ft_strlen(elem)) == 0
			&& env[i][ft_strlen(elem)] == '=')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

char		*ft_get_entry(t_cmd **cmd)
{
	char	*tmp;

	ft_read_line(&tmp, cmd);
	tmp = ft_exclamation(tmp);
	if (ft_onlyspc(tmp) == 1)
	{
		free(tmp);
		return (ft_strdup(""));
	}
	else
		return (tmp);
}

int			ft_isbuiltin(char *str)
{
	if (ft_strcmp(str, "unsetenv") == 0
	|| ft_strcmp(str, "exit") == 0
	|| ft_strcmp(str, "setenv") == 0
	|| ft_strcmp(str, "cd") == 0
	|| ft_strcmp(str, "echo") == 0
	|| ft_strcmp(str, "history") == 0)
		return (1);
	else
		return (0);
}
