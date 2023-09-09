# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 15:59:35 by htaheri           #+#    #+#              #
#    Updated: 2023/09/08 14:31:53 by htaheri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Name 			= pipex
CFLAGS 			= -Wall -Werror -Wextra -g

SRCS 			= src/main.c src/utils.c
SRCS_BONUS 		= src_bonus/main_final.c src_bonus/bonus_utils.c

OBJS        := $(SRCS:.c=.o)
OBJS_BONUS       := $(SRCS_BONUS:.c=.o)

LIBFT_DIR 	= lib/libft
LIBFT 		= $(LIBFT_DIR)/libft.a

GNL_DIR      =     lib/GNL
GNL          =     $(GNL_DIR)/libgnl.a


all: $(Name)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(GNL):
	@$(MAKE) -C $(GNL_DIR)

$(Name): $(LIBFT) $(GNL) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -lgnl -o $(Name)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<
	
bonus: $(Name) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -lgnl -o bonus_pipex
clean:
	@$(MAKE)  -C $(LIBFT_DIR) clean
	@$(MAKE)  -C $(GNL_DIR) clean
	rm -rf $(OBJS)
	rm -rf $(OBJS_BONUS)
	
fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(GNL_DIR) fclean
	rm -rf $(Name)
	rm -rf bonus_pipex

re: fclean all

.PHONY: all clean fclean re