# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 02:58:34 by erpascua          #+#    #+#              #
#    Updated: 2025/08/11 19:26:05 by erpascua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# .SILENT:

#******************************************************************************#
#									  CONFIG								   #
#******************************************************************************#

NAME		= 	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -Iinclude -I$(LIBFT_DIR)
RM			=	/bin/rm -f
                   
LIBFT_DIR	=	libft
LIBFT       =	$(LIBFT_DIR)/libft.a

# DEV: WARNING WILDCARD - To be removed
SRCS        = 	$(shell find src -name "*.c")

MAIN_SRC    = 	src/main.c

OBJ_DIR     =	obj
OBJS        =	$(SRCS:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS  =	$(BONUS_SRCS:bonus/%.c=$(OBJ_DIR)/bonus/%.o)
ALL_OBJS    =	$(OBJS) $(BONUS_OBJS)

#******************************************************************************#
#									   RULES								   #
#******************************************************************************#

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) 1>/dev/null

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "✅  $@ built"

$(OBJ_DIR)/src/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/bonus/%.o: bonus/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# DEV: Should probably be removed
bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(OBJS) $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(BONUS_OBJS) $(LIBFT) -o $(NAME_BONUS)
	@echo "✅  $@ built"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean 1>/dev/null
	@$(RM) -rf $(OBJ_DIR)
	@echo "✅  Objects files deleted"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean 1>/dev/null
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "✅  Binaries deleted"

re: fclean all

dev: 
	@make re 1>/dev/null
	@make clean 1>/dev/null
	@echo "✅  Libraries created and objects deleted"

.PHONY: all clean fclean re bonus dev
