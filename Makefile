GREEN = \033[38;5;2m
NORMAL = \033[38;5;255m
RED = \033[38;5;1m
BLUE = \033[38;5;4m
YELLOW = \033[1;33m

SRCS	=	source/minishell.c \
			source/parse/lexer.c \
			source/parse/check.c \
			source/parse/parser.c \
			source/parse/peek.c \
			source/prints/print_tree.c \
			source/prints/print_token.c \
			source/helper/error.c \
			source/helper/free.c \
			source/helper/list.c \
			source/exec/exec_existing_prog.c\
			source/exec/exec.c \
			source/built_in/built_in.c \
			source/built_in/cd_pwd.c \
			source/built_in/env.c \
			source/built_in/export.c \
			source/built_in/unset.c \
			source/built_in/echo.c \
			source/built_in/exit.c \
			source/environment/init_env.c \
			source/environment/var.c \
			source/expand/remove_and_expand.c \
			source/expand/just_expand.c \
			source/redirection/redirection.c \
			source/redirection/redirect_heredoc.c
# update later on the redirection

OBJS	= $(SRCS:.c=.o)

NAME	= minishell

GCC		= gcc

FLAGS	= -Wall -Wextra -Werror -fsanitize=address -g
# FLAGS	= -Wall -Wextra -Werror

HEADER_FILE = include/minishell.h

LIBFT_DIR = utils/libft

LIBFT_LIB = libft.a

all:	$(NAME)

$(NAME):	$(OBJS)
	$(MAKE) bonus -C $(LIBFT_DIR)
	$(GCC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT_DIR)/$(LIBFT_LIB) -lreadline
	@echo "$(GREEN)Minishell:Successfully compiled!$(NORMAL)"

%.o: %.c $(HEADER_FILE)
	@echo "$(YELLOW)Compiling minishell...$(NORMAL)"
	$(GCC) -c $< -o $(<:.c=.o)


clean:
	@echo "$(RED)Removing object files...$(NORMAL)"
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	@echo "$(GREEN)Removed object files!$(NORMAL)"

fclean: clean
	@echo "$(RED)Removing libft.a...$(NORMAL)"
	rm -f $(LIBFT_DIR)/libft.a
	@echo "$(RED)Removing minishell...$(NORMAL)"
	rm -f $(NAME)
	@echo "$(BLUE)Successfully fcleaned!$(NORMAL)"

re: fclean all

.PHONY:	clean fclean re
