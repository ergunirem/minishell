#include "../../include/minishell.h"

# define GREEN "\033[38;5;2m"
# define RESET "\033[38;5;255m"
# define RED "\033[38;5;1m"
# define BLUE "\033[38;5;4m"
# define PURPLE "\033[0;35m"
# define YELLOW "\033[0;33m"

void	print_tokens(t_token *list)
{
	printf("%s*********** TokenList ************%s\n\n", PURPLE, RESET);
	while (list)
	{
		if(list->type == CHAR_WORD)
			printf("%sType [%c]    Content [%s]\n", GREEN, list->type, list->content);
		else if(list->type == CHAR_PIPE)
			printf("%sType [%c]    Content [%s]\n", BLUE, list->type, list->content);
		else
			printf("%sType [%c]    Content [%s]\n", RED, list->type, list->content);
		list = list->next;
	}
	printf("\n%s**********************************%s\n\n", PURPLE, RESET);
}
