/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swann <swann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:20:38 by slegros           #+#    #+#             */
/*   Updated: 2018/05/22 20:06:40 by swann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct				s_blt
{
	char					*cmd;
	char					*opt;
	char					**args;
}							t_blt;

/*
** conversion.c
*/
void						ft_clean_cmd(t_blt cmd);
t_blt						ft_conversion_cd(char **entry);
t_blt						ft_conversion(char **entry);

/*
** exec_history_1.c
*/
int							ft_exec_history(t_blt cmd);

/*
** exec_history_2.c
*/
int							ft_history_d(char *arg);
int							ft_history_a(char **args, char opt);
int							ft_history_n(char **args);
int							ft_history_w(char **args, char opt);
int							ft_history_r(char **args);

/*
** exec_history_3.c
*/
int							ft_history_error(int mode, char *str, char c);
char						**ft_filecontent(void);

/*
** exec_exit.c
*/
int							ft_exec_exit(t_blt cmd);

/*
** exec_echo.c
*/
int							ft_exec_echo(char **entry);

/*
** exec_env_1.c
*/
int							ft_prexec_env(t_blt cmd, char **env, t_cmd *cmds);

/*
** exec_env_2.c
*/
int							ft_exec_env_args_2(char **tabz, char **tmp_env,
								t_cmd *cmds);
int							ft_exec_setenv(t_blt cmd, char **env);
int							ft_exec_unsetenv(t_blt cmd, char **env);

/*
** exec_env_error.c
*/
int							ft_env_error(char *str, int mode);

/*
** exec_cd_1.c
*/
int							ft_cd_error(int mode, char opt, char *str,
								char *tmp);
int							ft_exec_cd(t_blt cmd);

/*
** exec_cd_2.c
*/
int							ft_cd_path(char *path, char opt, int mode);

/*
** builtin_tools.c
*/
int							is_reg(char *file);
int							ft_check_name(char *name);
char						**ft_change_pwd(char **env, char *new_pwd);
int							ft_launch_builtin(char **tabz, char **env,
								t_cmd *cmds);

#endif
