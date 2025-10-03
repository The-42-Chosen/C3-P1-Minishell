# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 02:58:34 by erpascua          #+#    #+#              #
#    Updated: 2025/10/03 18:36:50 by erpascua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


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

SRCS        = 	src/built-in/cd.c \
				src/built-in/cd_folder.c \
				src/built-in/cd_home.c \
				src/built-in/cd_paths.c \
				src/built-in/cd_path_utils.c \
				src/built-in/cd_pwd.c \
				src/built-in/command_builtin.c \
				src/built-in/echo.c \
				src/built-in/env.c \
				src/built-in/env_utils.c \
				src/built-in/exit.c \
				src/built-in/export_args_utils.c \
				src/built-in/export.c \
				src/built-in/export_noarg_utils.c \
				src/built-in/export_utils.c \
				src/built-in/pwd.c \
				src/built-in/unset.c \
				src/exec/builtin_exec.c \
				src/exec/cmd_exec.c \
				src/exec/fd_utils.c \
				src/exec/launch_program.c \
				src/exec/launch_program_utils.c \
				src/exec/process.c \
				src/exec/redirect_input.c \
				src/exec/redirect_output.c \
				src/global/struct_init.c \
				src/main.c \
				src/parsing/command_setup.c \
				src/parsing/expand.c \
				src/parsing/expand_utils.c \
				src/parsing/inout.c \
				src/parsing/lexer.c \
				src/parsing/lexer_utils_2.c \
				src/parsing/lexer_utils.c \
				src/parsing/parsing_commands.c \
				src/parsing/parsing_data.c \
				src/parsing/parsing_main.c \
				src/parsing/parsing_redirections.c \
				src/parsing/pre_exec.c \
				src/parsing/resolved_path.c \
				src/parsing/stack.c \
				src/parsing/stack_utils.c \
				src/parsing/token.c \
				src/parsing/token_classification.c \
				src/parsing/token_handlers.c \
				src/parsing/token_validation.c \
				src/signals/sig_eof.c \
				src/signals/sig_int.c \
				src/utils/banner.c \
				src/utils/free_part_1.c \
				src/utils/free_part_2.c \
				src/utils/msh.c \
				src/utils/print_data.c \
				src/utils/print_pre_exec.c \
				src/utils/string_array_concat.c \
				src/utils/string_array_copy.c

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

val: all
	valgrind --suppressions=$$(pwd)/_dev_tools/.ignore_rl_leaks.supp --trace-children=yes --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all -s ./minishell

dev:
	@make re 1>/dev/null
	@make clean 1>/dev/null
	@echo "✅  Libraries created and objects deleted"

.PHONY: all clean fclean re dev val
