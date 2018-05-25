# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slegros <slegros@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/15 23:45:07 by slegros           #+#    #+#              #
#    Updated: 2018/05/22 17:11:50 by slegros          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	42sh
FLAG		=	-Werror -Wall -Wextra #-g3 -fsanitize=address 

PTH_LIBFT	=	libft/
LIBFT		=	$(PTH_LIBFT)libft.a
LNK_LIBFT	=	-L. $(LIBFT) -ltermcap

SRCS		=	srcs/main.c \
				srcs/main_exec.c \
				srcs/bonus.c \
				srcs/tools.c \
				srcs/sigleton.c \
				srcs/singleto.c \
				srcs/signal.c \
				srcs/term.c \
				srcs/get_env.c \
				srcs/get_exec_path.c \
				srcs/builtin/exec_echo.c \
				srcs/builtin/exec_exit.c \
				srcs/builtin/exec_env_1.c \
				srcs/builtin/exec_env_2.c \
				srcs/builtin/exec_env_error.c \
				srcs/builtin/exec_cd_1.c \
				srcs/builtin/exec_cd_2.c \
				srcs/builtin/conversion.c \
				srcs/builtin/exec_history_1.c \
				srcs/builtin/exec_history_2.c \
				srcs/builtin/exec_history_3.c \
				srcs/builtin/builtin_tools.c \
				srcs/line_edit/line_edit.c \
				srcs/line_edit/history.c \
				srcs/line_edit/exclamation.c \
				srcs/line_edit/exclamation_2.c \
				srcs/line_edit/exclamation_3.c \
				srcs/line_edit/hist_move_1.c \
				srcs/line_edit/hist_move_2.c \
				srcs/line_edit/hist_jump.c \
				srcs/line_edit/hist_edit.c \
				srcs/line_edit/hist_eot_1.c \
				srcs/line_edit/hist_eot_2.c \
				srcs/line_edit/hist_tools_1.c \
				srcs/line_edit/hist_tools_2.c \
				srcs/line_edit/hist_tools_3.c \
				srcs/line_edit/hist_tools_4.c \
				srcs/line_edit/hist_enter.c \
				srcs/line_edit/hist_tab.c \
				srcs/line_edit/hist_tab_search.c \
				srcs/line_edit/ft_select.c \
				srcs/line_edit/ft_select_tools.c \
				srcs/line_edit/ft_select_print.c \
				srcs/line_edit/ft_select_move.c \
				srcs/line_edit/ft_select_sel.c \
				srcs/exec/core/cmd.c \
				srcs/exec/core/cmd2.c \
				srcs/exec/core/utils.c\
				srcs/exec/lexer/lexer.c \
				srcs/exec/lexer/lexer_handler1.c \
				srcs/exec/lexer/lexer_handler2.c \
				srcs/exec/lexer/lexer_handler3.c \
				srcs/exec/lexer/lexer_print.c \
				srcs/exec/lexer/lexer_utils.c \
				srcs/exec/parser/parser.c \
				srcs/exec/parser/parser_quote.c \
				srcs/exec/ast/ast.c \
				srcs/exec/ast/ast_tree.c \
				srcs/exec/ast/ast_print.c \
				srcs/exec/ast/ast_operat.c \
				srcs/exec/ast/ast_redir.c \
				srcs/exec/exec/exec.c \
				srcs/exec/exec/heredoc.c \
				srcs/exec/exec/exec_redir.c \
				srcs/exec/exec/exec_operat.c \
				srcs/exec/exec/exec_core.c \
				srcs/exec/exec/exec_utils.c \
				srcs/exec/exec/exec_redir2.c \
				srcs/exec/print/print.c \
				srcs/exec/print/print_err.c \
				srcs/exec/print/print_err2.c \
				srcs/exec/utils/gnl.c \
				srcs/exec/utils/utils.c \
				srcs/exec/utils/utils2.c \
				srcs/exec/utils/free.c \
				srcs/exec/utils/fds.c \

OBJ 		=	$(SRCS:.c=.o)

INCLDS		=	-I $(PTH_LIBFT) -I includes/minishell.h
INCLDS_ALL	= includes/minishell.h includes/builtin.h includes/line_edit.h includes/vingtetunsh.h

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLAG) -o $@ $^ $(LNK_LIBFT)

$(LIBFT):
	make -C $(PTH_LIBFT)

%.o: %.c $(INCLDS_ALL)
	gcc $(FLAG) $(INCLDS) -c -o $@ $<

clean:
	rm -rf $(OBJ)
	make -C $(PTH_LIBFT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(PTH_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
