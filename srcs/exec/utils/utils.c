/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 14:17:41 by amottier          #+#    #+#             */
/*   Updated: 2018/05/16 11:49:29 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*add_slash(char *full_path)
{
	int len;

	len = ft_strlen(full_path);
	if (full_path[len - 1] != '/')
	{
		if (!(full_path = ft_strjoin(full_path, "/")))
			return (NULL);
	}
	else
	{
		if (!(full_path = ft_strdup(full_path)))
			return (NULL);
	}
	return (full_path);
}

char		*realloc_str(char *str1, char *str2)
{
	char *tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(str1)
				+ ft_strlen(str2) + 1));
	ft_strcpy(tmp, str1);
	ft_strcat(tmp, str2);
	free(str1);
	str1 = tmp;
	return (str1);
}
