NAME	= libft.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I $(INC)
RM		= rm -rf
AR		= ar rcs
LIB		= ranlib
INC		= inc/

SRCS_FILES = ft_strcmp.c ft_calloc.c ft_bzero.c ft_memset.c ft_strdup.c ft_strlen.c \
			 ft_strnstr.c ft_substr.c ft_free_array.c ft_isalnum.c ft_isalpha.c \
			 ft_isdigit.c ft_isprint.c ft_strjoin.c ft_superjoin.c ft_split.c \
			 ft_atoi.c ft_atoll.c ft_itoa.c ft_strncmp.c ft_isspace.c \
			 ft_putstr_fd.c ft_putendl_fd.c

SRCS_DIR	= srcs/
OBJS_DIR	= objs/
SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS_FILES	= $(SRCS_FILES:.c=.o)
OBJS		= $(addprefix $(OBJS_DIR), $(OBJS_FILES))

# Colors
BOLD_PURPLE	= \033[1;35m
BOLD_CYAN	= \033[1;36m
BOLD_YELLOW	= \033[1;33m
NO_COLOR	= \033[0m
DEF_COLOR 	= \033[0;39m
GRAY 		= \033[0;90m
RED 		= \033[0;91m
GREEN		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE 		= \033[0;94m
MAGENTA 	= \033[0;95m
CYAN 		= \033[0;96m
WHITE		= \033[0;97m

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@$(LIB) $(NAME)
	@echo "$(GREEN)libft.a compiled!\n$(DEF_COLOR)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@[ -d $(OBJS_DIR) ] || mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS_DIR)
	@echo "$(GREEN)libft$(YELLOW) cleaned$(DEF_COLOR)\n"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.SILENT: all $(NAME) $(OBJS) re clean fclean
.PHONY: all clean fclean re