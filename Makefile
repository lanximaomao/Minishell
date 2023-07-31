# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsun <lsun@student.hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 17:18:26 by lliu              #+#    #+#              #
#    Updated: 2023/07/31 16:18:42 by lsun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# formatting
DEF_COLOR	=	\033[0;39m
ORANGE		=	\033[0;33m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

ECHO		= echo

SRCS = 			mini_utils.c	free.c validator.c					\
				lexer.c expander.c expander_utils.c expander_utils2.c	\
				parser.c parser_utils.c									\
				env_var.c signal.c										\
				builtin_echo.c											\
				builtin_exit.c builtin_export.c							\
				builtin_unset.c builtin.c builtin_cd.c					\
				builtin_env.c builtin_pwd.c								\
				executor.c executor_child.c executor_files.c			\
				executor_utils.c
SRCSDEST = $(addprefix ./SRCS/, $(SRCS))

NAME = minishell
CC = cc
CFLAGS = -Werror -Wall -Wextra -I./libft_42/inc -g
LDFLAGS = -L./libft_42 -lft
FSANITIZE	= -fsanitize=address -g

RL_L = -lreadline -lhistory -L /Users/lsun/.brew/opt/readline/lib
RL_I = -I /Users/lsun/.brew/opt/readline/include/readline

all: $(NAME)
$(NAME): $(SRCSDEST) main.c includes/minishell.h
	@make -C libft_42
	@$(CC) $(LDFLAGS) $(SRCSDEST) -o $(NAME) $(RL_L) $(RL_I) main.c
	@$(ECHO) "$(YELLOW)[$(NAME)]:\t$(DEF_COLOR) $(GREEN) => Success!$(DEF_COLOR)"
clean:
	@make clean -C libft_42
	@rm -f $(OBJS) $(OBJ_BONUS)
	@$(ECHO) "$(BLUE)[$(NAME)]:\tobject files$(DEF_COLOR)$(GREEN) => Cleaned!$(DEF_COLOR)"

fclean: clean
	@make fclean -C libft_42
	@rm -f $(NAME)
	@$(ECHO) "$(CYAN)[$(NAME)]:\ttarget files$(DEF_COLOR)$(GREEN) => Cleaned!$(DEF_COLOR)"
re:	fclean all

norm:
	norminette builtin_exit.c | grep -v Norme -B1 || true
debug:
	@make -C libft_42
	@$(CC) $(CFLAGS) $(FSANITIZE) $(LDFLAGS)  $(RL_L) $(RL_I) $(SRCS) -o $(NAME)

.PHONY : all clean fclean re norm debug

