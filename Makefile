# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 10:13:27 by dgargant          #+#    #+#              #
#    Updated: 2025/02/07 10:50:23 by dgargant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gertru

CC	= gcc

HEADERS:= -I ./includes 

#CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3 $(HEADERS)
CFLAGS = -Wall -Werror -Wextra -g3 $(HEADERS)
#valgrind --leak-check=full --show-leak-kinds=all
#CFLAGS = -Wall -Werror -Wextra $(HEADERS) 
#valgrind --trace-children=yes --track-fds=yes --leak-check=full
#valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all
# valgrind --track-fds=yes --trace-children=yes --leak-check=full 
# --show-leak-kinds=all ./pipex README.md ls ls salida.txt

GPATH = libft

LIBFT_PATH = $(GPATH)/libft.a

# Colors
RED =			\033[0;31m
GREEN =			\033[0;92m
CYAN =			\033[0;96m
BLUE=			\033[0;34m
PURPLE=			\033[0;95m
YELLOW =		\033[0;93m
RESET=			\033[0m

SRCS :=	 $(addprefix sources/, \
	gertru.c	\
	$(addprefix parsing/,	\
	parsing_init.c	tokenizer_init.c	tokenizer_utils.c\
	tokenizer_counters.c	tokenizer_redirec.c)	\
	$(addprefix utils/,	\
	frees_2.c	frees.c	list_utils.c))

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	make _libft $(LIBFT_PATH)
	make print_title
	@echo "$(GREEN)Creando ejecutable"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_PATH) -o $(NAME) -lreadline
	@echo "Ejecutable Creado$(RESET)"


all : _libft $(NAME)

print_title:
	echo "$(PURPLE) ██████╗ ███████╗██████╗ ████████╗██████╗ ██╗   ██╗"
	echo "██╔════╝ ██╔════╝██╔══██╗╚══██╔══╝██╔══██╗██║   ██║"
	echo "██║  ███╗█████╗  ██████╔╝   ██║   ██████╔╝██║   ██║"
	echo "██║   ██║██╔══╝  ██╔══██╗   ██║   ██╔══██╗██║   ██║"
	echo "╚██████╔╝███████╗██║  ██║   ██║   ██║  ██║╚██████╔╝"
	echo " ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ $(RESET)"
                                                   


clean :
	rm -fr $(OBJS)
	@make clean -C $(GPATH)

fclean : clean
	rm -f  $(NAME)
	@make fclean -C $(GPATH)

re : fclean all

_libft :
	@make -C $(GPATH)

.PHONY: all clean fclean re print_title
.SILENT: print_title