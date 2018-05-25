/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vingtetunsh.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amottier <amottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:48:22 by ysalaun           #+#    #+#             */
/*   Updated: 2018/05/22 16:36:44 by amottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VINGTETUNSH_H
# define VINGTETUNSH_H

# include <libc.h>
# include <string.h>
# include <sys/xattr.h>

typedef struct			s_qots
{
	int					cursh;
	int					subsh;
	int					crosh;
	int					qu;
	int					dqu;
	int					bqu;
}						t_qots;

typedef int	t_token_type;
typedef int	t_char_type;

typedef struct			s_token
{
	char				*str;
	int					len;
	t_token_type		type;
	struct s_token		*next;
	struct s_token		*prev;
	int					fd_from;
	int					fd_to;
	char				*filename;
}						t_token;

typedef struct			s_btree
{
	struct s_btree		*parent;
	struct s_btree		*right;
	struct s_btree		*left;
	struct s_token		*data;
}						t_btree;

typedef struct			s_fds
{
	int					fd_stdin;
	int					fd_stdout;
	int					fd_stderr;
}						t_fds;

typedef struct			s_heredoc
{
	char				*content;
	char				*end_word;
	int					position;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct			s_cmd
{
	char				*command;
	int					give_me_more;
	int					debug;
	char				**envir;
	t_token				*head;
	t_btree				*ast;
	int					heredoc_mode;
	int					heredoc_total;
	int					heredoc_done;
	t_heredoc			*heredoc;
	t_heredoc			*heredoc1;
}						t_cmd;

enum	e_char_type
{
	CHAR_NONE,
	CHAR_LETTER,
	CHAR_BLANK,
	CHAR_NEWLINE,
	CHAR_DQUOTE,
	CHAR_SQUOTE,
	CHAR_AND,
	CHAR_DIGIT,
	CHAR_SEMICOLON,
	CHAR_COMPARE,
	CHAR_PIPE,
	CHAR_BACKSLASH
};

enum	e_token_type
{
	TOKEN_NONE,
	TOKEN_BLANK,
	TOKEN_NEWLINE,
	TOKEN_WORD,
	TOKEN_SQUOTE,
	TOKEN_BQUOTE,
	TOKEN_DQUOTE,
	TOKEN_IO_NUMBER,
	TOKEN_LESSGREAT,
	TOKEN_GREAT,
	TOKEN_LESS,
	TOKEN_DLESS,
	TOKEN_DGREAT,
	TOKEN_LESSAND,
	TOKEN_ANDGREAT,
	TOKEN_GREATAND,
	TOKEN_PIPE,
	TOKEN_OR_IF,
	TOKEN_AND_IF,
	TOKEN_AND,
	TOKEN_SEMI
};

/*
**	---------------------------  CORE --------------------------------
*/

/*
**	cmd.c
*/
t_cmd					*set_cmd(char *line, t_cmd **cmd);
t_cmd					*init_cmd(void);
t_cmd					*reset_cmd(t_cmd **cmd);
t_cmd					*insert_mode(char *line, t_cmd **cmd);
t_cmd					*heredoc_mode(char *line, t_cmd **cmd);
int						check_backslash(char *str);
int						last_is_oper(t_token *head, char *cmd);
/*
**	main.c
*/
char					*get_home(char *pwd);
void					launch_exec(t_cmd **cmd);
void					parsing_ok(t_cmd **cmd);
void					enter(char *line, t_cmd **cmd);
void					end_enter(t_cmd **cmd);
/*
**	utils.c
*/
int						has_line(char *line);

/*
**	-------------------------------- PRINT -------------------------------------
**	print.c
*/
void					print_prompt(int i);
/*
**	print_err.c
*/
void					err_no_cmd(char *cmd);
int						err_no_fd(int fd_nbr);
int						err_no_file(char *msg);
int						err_no_file_perm(char *msg);
void					print_err(char *name, int type);
/*
**	print_err2.c
*/
void					parsing_error(char *str);
/*
**	-------------------------------- LEXER -------------------------------------
**	lexer.c
*/
void					handle_switch(t_token **head, char **cmd,
							int start, char *tmp);
void					get_token(t_token **head, char *cmd);
/*
**	lexer_handler1.c
*/
void					handle_blank(char **cmd, t_token **head);
void					handle_semicolon(char **cmd, t_token **head);
void					handle_dquote(char **cmd, t_token **head, char *tmp,
							int start);
void					handle_squote(char **cmd, t_token **head, char *tmp,
							int start);
void					handle_newline(char **cmd, t_token **head);
/*
**	lexer_handler2.c
*/
void					handle_pipe(char **cmd, t_token **head);
void					handle_and(char **cmd, t_token **head);
void					handle_word(char **cmd, t_token **head, char *tmp,
							int start);
void					handle_digit(char **cmd, t_token **head, char *tmp,
							int start);
int						ft_strnchr(const char *str, int c, int start);
/*
**	lexer_handler3.c
*/
void					handle_compare_great(char **cmd, t_token **head);
void					handle_compare_less(char **cmd, t_token **head);
/*
**	lexer_print.c
*/
void					print_tokens(t_token *head);
void					lexer_error(void);
/*
**	lexer_utils.c
*/
int						get_ascii_type(int c);
t_token					*new_elem(char *str, t_char_type type);
void					add_token(t_token **head, t_char_type type, char *str);
char					*crop_str(char *tmp, char *cmd, int start, int diff);
char					*process_backslash(char *s1);

/*
**	-------------------------------- PARSER ------------------------------------
**	parser.c
*/

t_token_type			get_type(t_token_type type);
int						check_first(t_token *head);
int						check_last(t_token *head);
int						check_middle(t_token *head);
int						check_unsopprted_tokens(t_token *head);
int						parsing(t_token *head);
/*
**	parser_quote.c
*/
int						gestion_quotes2(char *cmd);
int						check_unsopprted_tokens(t_token *head);
/*
**	-------------------------------- UTILS -------------------------------------
**	fds.c
*/
t_fds					*get_fds(void);
void					restore_fds(void);
/*
**	free.c
*/
void					free_heredoc(t_heredoc *elem);
void					free_token(t_token *elem);
void					free_tabz(char **tabz);
/*
**	gnl.c
*/
int						get_next_line(const int fd, char **line);
/*
**	utils.c
*/
char					**get_path(t_cmd *cmd);
char					*add_slash(char *full_path);
char					*realloc_str(char *str1, char *str2);
/*
**	utils2.c
*/
int						open_file(char *filename, int append, int read);
int						check_cmd_syntax(char **tabz);
void					ft_close(int lnk);
int						ft_checks(void);
/*
**	-------------------------------- EXEC -------------------------------------
**	exec.c
*/
char					**tabz_pocess(t_token *tkn, int i);
char					**tabz_from_token(t_token *tkn);
int						exec(char **tabz, int to_fork, t_cmd *cmd);
int						start_exec(t_btree *ast, int to_fork, t_cmd *cmd);
int						exec_recursive(t_btree *ast, int to_fork, t_cmd *cmd);
/*
**	exec_core.c
*/
int						run_cmd(char *path, char **tabz, t_cmd *cmd,
							int to_fork);
char					*get_executable(char *name, char **path);
int						bin_exist(char *path);
int						not_bultin(char **tabz, t_cmd *cmd, int to_fork);
char					*browse_dir(char *name, char *path, char *folder_name);
/*
**	exec_operat.c
*/
int						exec_semicolon(t_btree *ast, t_cmd *cmd);
int						exec_and(t_btree *ast, t_cmd *cmd);
int						exec_or(t_btree *ast, t_cmd *cmd);
int						exec_pipe(t_btree *ast, t_cmd *cmd);
void					dup_both(int fd);
int						exec_write_and_closed(t_btree *ast, int to_fork,
							t_cmd *cmd);
/*
**	exec_redir.c
*/
int						exec_write(t_btree *ast, int to_fork, t_cmd *cmd);
int						exec_andwrite(t_btree *ast, int to_fork, t_cmd *cmd);
int						exec_write_and_closed(t_btree *ast, int to_fork,
							t_cmd *cmd);
int						exec_write_and(t_btree *ast, int to_fork, t_cmd *cmd);
int						exec_read_and(t_btree *ast, int to_fork, t_cmd *cmd);
int						exec_read(t_btree *ast, int to_fork, t_cmd *cmd);
int						exec_heredoc(t_btree *ast, int to_fork, t_cmd *cmd);
/*
**	heredoc.c
*/
void					add_heredoc(t_cmd **cmd, int pos, char *end_word);
int						parse_heredoc(t_cmd **cmd);
int						last_is_oper(t_token *head, char *cmd);
/*
**	-------------------------------- BUILTINS --------------------------------
**	builtins_exit.c
*/
int						ft_exit(void);
/*
**	-------------------------------- AST -------------------------------------
**	ast.c
*/
t_btree					*split_cmd(t_token *head);
void					gen_tree_prefix(t_btree *ast);
t_btree					*create_ast(t_token *head);
/*
**	ast_operat.c
*/
t_token					*has_operator(t_token *head);
t_btree					*ast_operator(t_token *node);
/*
**	ast_print.c
*/
void					print_tree_prefix(t_btree *ast);
/*
**	ast_redir.c
*/
t_token					*has_redirection(t_token *head);
t_token					*handle_redir_left(t_token *node);
t_token					*handle_redir_right(t_token *node);
t_btree					*ast_redirection(t_token *node, t_token *head);
/*
**	ast_tree.c
*/
t_btree					*new_tree(t_token *token);
t_btree					*join_tree(t_btree *left, t_btree *right,
							t_token *token);
void					clean_tree(t_btree *ast);

#endif
