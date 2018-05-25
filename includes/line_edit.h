/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slegros <slegros@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 11:44:50 by slegros           #+#    #+#             */
/*   Updated: 2018/05/23 14:14:53 by slegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDIT_H
# define LINE_EDIT_H

typedef struct winsize		t_wsize;

typedef struct				s_h
{
	char					**hist;
	int						i;
	int						j;
	int						start;
}							t_h;

typedef struct				s_grl
{
	int						row;
	int						col;
	size_t					max_len;
	int						ar_len;
}							t_grl;

typedef struct				s_prt
{
	int						row;
	int						col;
	int						pls;
	int						*select;
	int						i;
}							t_prt;

/*
** line_edit.c
*/
void						ft_read_line(char **line, t_cmd **cmd);

/*
** history.c
*/
t_h							ft_history(int mode, char *buf, int move);

/*
** hist_move_1.c
*/
void						ft_hist_supermove(t_h *the, int mode, int move);
void						ft_hist_move_left(t_h *the, int val);
void						ft_hist_move_right(t_h *the, int val);

/*
** hist_move_2.c
*/
void						ft_hist_move(t_h *the, int modove);

/*
** hist_jump.c
*/
void						ft_hist_jump(t_h *the, int move, t_wsize w);

/*
** hist_edit.c
*/
char						*ft_hist_upk_save(char *to_save, int mode);
void						ft_hist_upk(t_h *the, int key);
void						ft_hist_edit(t_h *the, char *buf, int mode);

/*
** hist_enter.c
*/
void						ft_hist_enter(t_h *the, char **save_hist, int mode);

/*
** hist_eot_1.c
*/
char						**ft_hist_eot_search_dir(char *t1);
char						**ft_hist_eot_search_cmd(char *t1);
char						**ft_hist_eot_search_env(char *t1);
void						ft_hist_eot(t_h *the, int mode);

/*
** hist_eot_2.c
*/
void						ft_hist_eot_search(char *t1, int i);
char						**ft_hist_eot_search_cmd_init(char *t1);
char						**ft_hist_eot_search_check(char **list);

/*
** hist_tools_1.c
*/
void						ft_hist_return(t_h the, int mode);
char						**ft_hist_init(t_h *the, int mode);
char						**ft_hist_restore(char **hist, char **save_hist);
void						ft_hist_print_spe(t_h *the, int mode);
int							nbl(void);

/*
** hist_tools_2.c
*/
void						ft_hist_print_spe_eol(t_h *the, int j_line,
								t_wsize w);
int							is_dir(char *file);
void						ft_hist_merge(t_h *the);
void						ft_hist_newhist(t_h *the);
char						**ft_hist_getcontent(char *path, int mode);

/*
** hist_tools_3.c
*/
void						ft_hist_getfile(t_h *the);
int							ft_hist_savefile_bis(char **hist, char *path);
int							ft_hist_savefile(char **hist, char **env);

/*
** hist_tools_4.c
*/
char						**ft_mystrsplit(char *str, char c, int nb);
char						**ft_dbarr_dir(char *dir, char *file, int mode);
t_grl						ft_get_nb(char **ar_list, struct winsize w);
void						ft_print_space(int max_len, int len_elem);
char						**ft_proper_list(char **list);

/*
** hist_tab.c
*/
void						ft_hist_tab_write(char **name, t_h *the);
void						ft_hist_tab(t_h *the);

/*
** hist_tab_search
*/
void						ft_hist_tab_search(char *t1, t_h *the, int in,
								t_wsize w);

/*
** ft_select.c
*/
char						**ft_select(char **list);

int							ft_get_pos(int pos, int mode);

/*
** ft_select_sel.c
*/
int							*ft_sel(int len, int mode, int ed);

/*
** ft_select_tools.c
*/
char						**ft_add_args(char **ar_list, int *select,
								int mode);
int							ft_set_pos(char *entry, t_grl nb, int pos,
								char **ar_list);
/*
** ft_select_move.c
*/
int							ft_move(t_grl nb, int pos, char *entry);

/*
** ft_select_print.c
*/
void						ft_print(char **ar_list, t_grl nb, int pos,
								struct winsize w);

/*
** exclamation.c
*/
char						*ft_exclamation(char *str);

/*
** exclamation_2.c
*/
char						*ft_getevent(char *name, int mode, int start,
								char *str);
char						*ft_exclamsearchint(char *tmp);
char						*ft_exclamsearchchar(char *tmp, int mode);

/*
** exclamation_3.c
*/
char						*ft_exclam_error(char *tmp, char *str, int mode);
char						*ft_excla_replace(char *str, char *new,
								int start, int end);

#endif
