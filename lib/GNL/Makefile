# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/27 16:37:47 by htaheri           #+#    #+#              #
#    Updated: 2023/07/27 17:51:20 by htaheri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = get_next_line.c get_next_line_utils.c

# BONUS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c


OBJS_SRC = $(SRCS:.c=.o)
# OBJS_BONUS = $(BONUS_SRC:.c=.o)

NAME = libgnl.a
all: $(NAME)
$(NAME): $(OBJS_SRC)
	ar rcs $(NAME) $(OBJS_SRC)

# bonus: $(OBJS_BONUS)
# 	ar rcs $(NAME) $(OBJS_BONUS)

clean:
	rm -f $(OBJS_SRC)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re