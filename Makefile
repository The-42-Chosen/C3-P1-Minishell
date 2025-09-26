# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 02:58:34 by erpascua          #+#    #+#              #
#    Updated: 2025/09/26 16:43:22 by erpascua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

#******************************************************************************#
#									  CONFIG								   #
#******************************************************************************#

NAME		= 	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -Iinclude -I$(LIBFT_DIR) -MMD -MP -g
LDFLAGS		=	-lreadline -ltermcap -lncurses

RM			=	/bin/rm -f

LIBFT_DIR	=	libft
LIBFT       =	$(LIBFT_DIR)/libft.a

# DEV: WARNING WILDCARD - To be removed
SRCS        = 	$(shell find src -name "*.c")

MAIN_SRC    = 	src/main.c

OBJ_DIR     =	obj
OBJS        =	$(SRCS:%.c=$(OBJ_DIR)/%.o)
ALL_OBJS    =	$(OBJS)

#******************************************************************************#
#									   RULES								   #
#******************************************************************************#

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) 1>/dev/null

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@echo "✅  Billyshell built"

$(OBJ_DIR)/src/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean 1>/dev/null
	@$(RM) -rf $(OBJ_DIR)
	@echo "✅  Objects files deleted"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean 1>/dev/null
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "✅  Binaries deleted"

re: fclean all

valgrind: all
	valgrind --suppressions=./_dev_tools/.ignore_rl_leaks.supp --trace-children=yes --leak-check=full --track-origins=yes --track-fds=yes -s ./minishell

dev:
	@make re 1>/dev/null
	@make clean 1>/dev/null
	@echo "✅  Libraries created and objects deleted"

.PHONY: all clean fclean re dev
