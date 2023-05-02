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

SRCS = 		main.c minishell.c mini_utils.c			\
				lexer.c expander.c parser.c				\
				builtin.c env.c	executor.c signal.c# test_lliu.c #
OBJS = $(SRCS:.c=.o)

SRCS_TEST =		main.c minishell.c mini_utils.c			\
				lexer.c expander.c parser.c				\
				builtin.c env.c	executor.c # test_lliu.c #signal.c

NAME = minishell
CC = cc
CFLAGS = -I./libft_42/inc
LDFLAGS = -L./libft_42 -lft
FSANITIZE	= -fsanitize=address -g3
#READLINE_DIR = $(shell brew --prefix readline)
RL_L = -lreadline -L /Users/lsun/.brew/opt/readline/lib
RL_I = -I /Users/lsun/.brew/opt/readline/include/readline


all: $(NAME)
$(NAME): $(OBJS)
	@git submodule update --init --recursive
	@cd libft_42 && git pull origin main
	@make -C libft_42
	@$(CC) $(LDFLAGS) $(OBJS) -o $(NAME) $(RL_L) $(RL_I)
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
	@git submodule update --init --recursive
	@cd libft_42 && git pull origin main
	@make -C libft_42
	$(CC)  -I./libft_42/inc $(LDFLAGS)  $(RL_L) $(RL_I) $(SRCS_TEST) -g -o test

.PHONY : all clean fclean re norm debug

