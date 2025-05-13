# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ifluxa-c <ifluxa-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/02 00:00:00 by dgomez-b          #+#    #+#              #
#    Updated: 2025/04/29 12:22:34 by ifluxa-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
INC			=	./includes/
LIBS		=	./libs/
BIN			=	./.bin/
SRC			=	./src/
SRCS		=	main.c \
				file_translator/file_translator.c \
				var_translator/var_translator.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \
				freedom/freedom.c \
				lexer/lexer.c \
				parser/parser.c \
				path/path.c \
				executor/executor.c \
				executor/help_executor.c \
				executor/help_executorII.c \
				history/history.c \
				builtins/builtins.c \
				builtins/builtinsII.c \
				builtins/help_builtins.c \
				errors/errors.c \
				checker/checker.c \
				aux_main/aux_main.c \
				aux_main/aux_mainII.c \
				signals/signals.c \
				signals/signals2.c \
				exitno/exitno.c
OBJS		=	$(addprefix $(BIN), $(SRCS:.c=.o))
LIBFT		=	$(LIBS)libft/libft.a
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3

all			:	$(NAME)
$(BIN)%.o	:	$(SRC)%.c
				@ mkdir -p $(dir $@)
				@ $(CC) $(CFLAGS) -c -o $@ $^ -I$(INC) -I $(LIBS)
%.a			:
				@ make -sC $(dir $@)
$(NAME)		:	$(LIBFT) $(OBJS)
				@ $(CC) $(CFLAGS) -o $@ $^ -L$(dir $(LIBFT)) -lft -lreadline
				@ echo Program compilled
clean		:
				@ make -sC $(dir $(LIBFT)) clean
				@ rm -rf $(BIN)
				@ echo Program object files deleted
fclean		:
				@ make -sC $(dir $(LIBFT)) fclean
				@ rm -rf $(BIN)
				@ echo Program object files deleted
				@ rm -f $(NAME)
				@ echo Program deleted
re			:	fclean all
.PHONY		:	all clean fclean re
