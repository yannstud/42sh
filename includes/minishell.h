/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:38:09 by slegros           #+#    #+#             */
/*   Updated: 2018/05/16 17:11:31 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <pwd.h>
# include <grp.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <signal.h>
# include <time.h>
# include <sys/socket.h>
# include <sys/ioctl.h>
# include <netinet/in.h>
# include <net/if.h>
# include <arpa/inet.h>
# include <dirent.h>
# include <fcntl.h>
# include "vingtetunsh.h"
# include "line_edit.h"
# include "builtin.h"

typedef struct sockaddr_in	t_sockad;

/*
** mainc.c
*/
void						ft_launchshell(void);

/*
** sigleton.c
*/
char						*ft_path(int mode, char *path);
char						**ft_env(char **env, int mode);
int							ft_button_select(int mode, int val);
int							ft_exit_value(int mode, int val);
int							ft_button_line(int mode, int val);

/*
** singleto.c
*/
pid_t						ft_pid(pid_t pid, int mode);
int							ft_control_c(int mode, int val);
t_wsize						ft_get_winsize(int mode);
int							ft_sigupk(int mode, int val);
char						*ft_create_line(char *line, char *tmp);

/*
** get_env.c
*/
char						**ft_get_env(void);

/*
** bonus.c
*/
char						*ft_where(int mode, char *str);
void						ft_hello_bye(char *col);
void						ft_welcome(char **env);

/*
** tools.c
*/
char						*ft_get_elem(char **env, char *elem);
int							ft_get_elemi(char **env, char *elem);
char						*ft_get_entry(t_cmd **cmd);
int							ft_isbuiltin(char *str);

/*
** get_exec_path.c
*/
char						*ft_getpath(char *cmd, char **env);

/*
** term.c
*/
void						ft_term_check(char **env);
struct termios				ft_term(int mode);
void						ft_term_reset(void);

/*
** signal.c
*/
void						ft_signal(void);

#endif
