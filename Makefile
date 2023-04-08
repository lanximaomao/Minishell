# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srall <srall@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/08 01:46:27 by srall             #+#    #+#              #
#    Updated: 2023/04/08 01:57:40 by srall            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = minishell.c

OBJS = $(SRCS:.c=.o)

SRCS_TEST =		test.c
OBJS = $(SRCS_TEST:.c=.o)

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror
# INCLUDE = -lreadline
# NAME_BONUS = minishell_bonus

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

all: $(NAME)
$(NAME):	$(OBJS)
	@git submodule update --init --recursive
	@make -C libft_42
	@$(CC) $(FLAGS) $(OBJS) -I libft_42/libft.a -o $(NAME)
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
	norminette $(SRCS) | grep -v Norme -B1 || true
debug:
	$(CC) $(FLAGS) $(SRCS_TEST) -I libft_42/libft.a -o test
	
.PHONY : all clean fclean re norm debug

