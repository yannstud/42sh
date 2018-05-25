/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_eot_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 11:17:41 by slegros           #+#    #+#             */
/*   Updated: 2018/05/10 12:32:37 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			**ft_hist_eot_search_dir(char *t1)
{
	char	*dir;
	char	*file;
	char	*tmp;
	char	**list;

	if (t1[0] == '>' || t1[0] == '<')
		t1 = ft_strrem(t1, 0);
	if (t1[0] != '/')
	{
		tmp = getcwd(NULL, 0);
		if (ft_strncmp(t1, "~/", 2) == 0)
			t1 = ft_strrem(t1, 0);
		else
			t1 = ft_strinsert(t1, '/', 0);
		t1 = ft_strjoinfree(tmp, t1, 3);
	}
	dir = ft_strsub(t1, 0, ft_strirchr(t1, '/') + 1);
	file = ft_strsub(t1, ft_strirchr(t1, '/') + 1,
		ft_strlen(t1) - (ft_strirchr(t1, '/') + 1));
	list = ft_dbarr_dir(dir, file, 1);
	ft_strdel(&t1);
	free(file);
	free(dir);
	return (list);
}

char			**ft_hist_eot_search_cmd(char *t1)
{
	char	**list;
	char	*tmp;
	char	**path;
	int		i;
	char	**tmp2;

	if (t1[0] == '&' || t1[0] == ';' || t1[0] == '|' || t1[0] == '`')
		t1 = ft_strrem(t1, 0);
	list = ft_hist_eot_search_cmd_init(t1);
	if ((tmp = ft_get_elem(ft_env(NULL, 0), "PATH")) != NULL)
	{
		path = ft_strsplit(tmp, ':');
		i = -1;
		while (path[++i] != NULL)
		{
			tmp2 = ft_dbarr_dir(path[i], t1, 1);
			if (tmp2 != NULL)
				list = ft_dbarrjoinfree(list, tmp2, 3);
		}
		ft_dbarr_free(path);
		free(tmp);
	}
	ft_strdel(&t1);
	list = ft_hist_eot_search_check(list);
	return (list);
}

char			**ft_hist_eot_search_env(char *t1)
{
	char	**env;
	int		i;
	char	**list;

	env = ft_dbarrdup(ft_env(NULL, 0));
	i = ft_dbarrlen(env) - 1;
	if (!(list = (char **)malloc(sizeof(char *) * 1)))
		return (NULL);
	list[0] = NULL;
	t1 = ft_strrem(t1, 0);
	while (i >= 0)
	{
		if (ft_strncmp(t1, env[i], ft_strlen(t1)) == 0)
		{
			env[i] = ft_strsubf(env[i], 0, ft_strichr(env[i], '='));
			env[i] = ft_strinsert(env[i], '$', 0);
			list = ft_dbarr_add(list, env[i]);
		}
		i--;
	}
	ft_dbarr_free(env);
	ft_strdel(&t1);
	list = ft_hist_eot_search_check(list);
	return (list);
}

static void		ft_hist_eot_2(t_h *the)
{
	char	*t1;
	char	*t2;
	int		in;

	in = the->j - 1;
	t1 = ft_strnew(0);
	t2 = ft_strdup(the->hist[the->i]);
	while (in >= 0 && t2[in] >= 33 && t2[in] <= 126)
	{
		if (t2[in] != 39 && t2[in] != 34 && t2[in] != 92)
			t1 = ft_strinsert(t1, t2[in], 0);
		if (t2[in] == '$' || t2[in] == '&' || t2[in] == ';'
			|| t2[in] == '|' || t2[in] == '`' || t2[in] == ')'
			|| (t2[in] == '-' && t2[in - 1] == ' ')
			|| t2[in] == '<' || t2[in] == '>')
			break ;
		in--;
	}
	ft_hist_eot_search(t1, in);
	free(t2);
}

void			ft_hist_eot(t_h *the, int mode)
{
	t_blt	cmd;

	if (ft_strlen(the->hist[the->i]) == 0 && (mode == 1 || mode == 3))
	{
		cmd.cmd = ft_strdup("exit");
		cmd.opt = NULL;
		cmd.args = ft_dbarrnew(1);
		cmd.args[0] = ft_strdup("129");
		ft_exec_exit(cmd);
	}
	else
	{
		if (the->j != ((int)ft_strlen(the->hist[the->i])))
			ft_hist_edit(the, NULL, 9);
		else
			ft_hist_eot_2(the);
	}
}
