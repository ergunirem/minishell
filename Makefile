GREEN = \033[38;5;2m
NORMAL = \033[38;5;255m
RED = \033[38;5;1m
BLUE = \033[38;5;4m
YELLOW = \033[1;33m

SRCS	= minishell.c \
			lexer.c \

OBJS	= $(SRCS:.c=.o)

NAME	= minishell

GCC		= gcc

# -fsanitize=address -g
FLAGS	= -Wall -Wextra -Werror -fsanitize=address -g

HEADER_FILE = minishell.h

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
