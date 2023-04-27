# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aessakhi <aessakhi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 21:28:41 by aessakhi          #+#    #+#              #
#    Updated: 2022/06/23 12:24:32 by aessakhi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/main.c	\
			srcs/check_pipe.c \
			srcs/check_tokens.c \
			srcs/check_redir.c \
			srcs/check_words.c \
			srcs/check_cmd.c \
			srcs/cmd_type.c \
			srcs/create_cmd.c \
			srcs/create_cmd_2.c \
			srcs/create_redir.c \
			srcs/create_tokens.c \
			srcs/delete_tokens.c \
			srcs/env_utils.c \
			srcs/exec.c \
			srcs/exec_pipe.c \
			srcs/exec_pipe_2.c \
			srcs/exec_bin.c \
			srcs/exec_bin_utils.c \
			srcs/redir_builtins.c \
			srcs/redir_bin.c \
			srcs/expand.c \
			srcs/expand_utils.c \
			srcs/free.c \
			srcs/free_2.c \
			srcs/get_token.c \
			srcs/get_token_quotes.c \
			srcs/init.c \
			srcs/lex_utils.c \
			srcs/print_utils.c \
			srcs/signals.c \
			srcs/signals_exec.c \
			srcs/tokens.c \
			srcs/ft_cd.c \
			srcs/ft_unset.c \
			srcs/ft_env.c \
			srcs/ft_exit.c \
			srcs/ft_export.c \
			srcs/ft_export2.c \
			srcs/ft_pwd.c \
			srcs/ft_echo.c \
			srcs/redir_pipe.c \
			srcs/expand_first.c \
			srcs/get_next_line_2.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c

OBJS	= ${SRCS:.c=.o}

CFLAGS	= -Wall -Wextra -Werror

NAME	= minishell

RM		= rm -f

all: ${NAME}

$(NAME):	${OBJS}
	make all -C libft/
	gcc -o ${NAME} ${SRCS} -lreadline libft/libft.a ${CFLAGS}


clean:
	${RM} ${OBJS}
	make clean -C libft/

fclean: clean
	${RM} ${NAME}
	make fclean -C libft/

re:		fclean all

.PHONY:	all clean fclean re bonus
