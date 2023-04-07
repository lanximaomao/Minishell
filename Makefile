NAME = minishell

SRCS = minishell.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

INCLUDE = -lreadline

all: $(NAME)

$(NAME):$(OBJS)
	make -C libft all
	make -C libft bonus
	cc $(FLAGS) $(SRCS) $(INCLUDE) -o $(NAME) libft/libft.a

$(OBJS):$(SRCS)
	cc -c $(SRCS)

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean:clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
