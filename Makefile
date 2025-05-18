# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pavicent <pavicent@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 10:13:27 by dgargant          #+#    #+#              #
#    Updated: 2025/05/18 23:14:58 by pavicent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	   = minishell

CC          = cc

CFLAGS      = -Wall -Wextra -Werror -g3 -I$(INC) -I$(LIBFT_DIR)inc/
LDFLAGS     = -L$(LIBFT_DIR) -lft

INC         = inc/

LIBFT_DIR   = libft/
LIBFT       = $(LIBFT_DIR)libft.a

OBJS_DIR    = objs/

# Colores
RED         = \033[0;31m
GREEN       = \033[0;92m
CYAN        = \033[0;96m
BLUE        = \033[0;34m
PURPLE      = \033[0;95m
YELLOW      = \033[0;93m
RESET       = \033[0m
BOLD_CYAN   = \033[1;96m

SRCS_DIR    = sources/

SRCS_FILES := \
	gertru.c signals.c \
	$(addprefix parsing/, parsing_init.c tokenizer_init.c tokenizer_utils.c tokenizer_counters.c tokenizer_redirec.c syntax_aut.c expand_init.c move_quotes.c) \
	$(addprefix utils/, frees_2.c frees.c list_utils.c length.c prints.c init_env.c) \
	$(addprefix execs/, execute.c builtins.c ft_cd.c ft_exit.c executor_cmds.c exec_cmd.c redirs.c unset.c get_pwd.c export.c) \
	$(addprefix files/, admin_files.c utils_files.c)

OBJS_FILES  = $(SRCS_FILES:.c=.o)

SRCS        = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS        = $(addprefix $(OBJS_DIR), $(OBJS_FILES))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "Compiling $(BLUE)$(NAME)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "\n$(GREEN)$(NAME) compiled!$(RESET)"
	@echo "$(BOLD_CYAN)\n------------\n| Done! 👌 |\n------------$(RESET)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@[ -d $(dir $@) ] || mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "Compiling $(BLUE)libft$(RESET)\n"
	@make -sC $(LIBFT_DIR)

clean:
	rm -rf $(OBJS_DIR)
	make fclean -sC $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	@echo "$(GREEN)$(NAME)$(YELLOW) cleaned$(RESET)"

re: fclean all

.PHONY: all clean fclean re
.SILENT: all clean fclean
