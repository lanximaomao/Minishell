# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: linlinsun <linlinsun@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 15:48:08 by linlinsun         #+#    #+#              #
#    Updated: 2023/02/19 18:34:47 by linlinsun        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_itoa.c ft_memchr.c ft_strchr.c ft_strrchr.c ft_memcmp.c ft_strdup.c ft_strtrim.c\
ft_atoi.c ft_memcpy.c ft_striteri.c ft_substr.c ft_bzero.c ft_memmove.c ft_strjoin.c ft_tolower.c\
ft_calloc.c ft_memset.c ft_strlcat.c ft_toupper.c ft_isalnum.c ft_putchar_fd.c ft_strlcpy.c\
ft_isalpha.c ft_putendl_fd.c ft_strlen.c ft_isascii.c ft_putnbr_fd.c ft_strmapi.c\
ft_isdigit.c ft_putstr_fd.c ft_strncmp.c ft_isprint.c ft_split.c ft_strnstr.c\
get_next_line.c ft_strlen_param.c ft_printf.c ft_hexa_deci.c ft_printf_ptr.c ft_printf_utils.c\
ft_digit_num.c

BONUS_SRCS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstdelone_bonus.c\
ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstclear_bonus.c\
ft_lstmap_bonus.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
CFLAGS = -c -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	cc $(CFLAGS) $(SRCS)
	ar -rcs $(NAME) $(OBJS)

bonus: $(BONUS_OBJS)

$(BONUS_OBJS):
	cc $(CFLAGS) $(BONUS_SRCS)
	ar -rus $(NAME) $(BONUS_OBJS)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
