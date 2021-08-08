#include "../../include/minishell.h"

#define GREEN "\033[38;5;2m"
#define RESET "\033[38;5;255m"
#define RED "\033[38;5;1m"
#define BLUE "\033[38;5;4m"
#define PURPLE "\033[0;35m"
#define YELLOW "\033[0;33m"

/*  Input String: < infile cat -e | wc | cat -e > outfile

**	Expected Tree Output:
	PIPE(
		CMD ( [<] [infile] [cat] [-e] )
		PIPE (
			CMD ( [wc] )
			CMD ( [cat] [-e] [>] [outfile] )
		)
	)
*/
void	indent(size_t spaces)
{
	for (size_t i = 0; i < spaces; i++)
	{
		putchar(' ');
	}
}

void	print_pipeline(t_pipe_node pipe, size_t spaces)
{
	printf("%sPIPE (\n%s", RED, RESET);
	visit_tree(pipe.left, spaces + 2);
	visit_tree(pipe.right, spaces + 2);
	indent(spaces);
	printf("%s)\n%s", RED, RESET);
}

void	print_command(t_cmd_node cmd)
{
	t_token	*token;

	token = cmd.tokens;
	printf("%sCMD ( %s", GREEN, RESET);
	while (token)
	{
		if (token->type == CHAR_WORD)
			printf("%s[%s] ", BLUE, token->content);
		else
			printf("%s[%c] ", BLUE, token->type);
		token = token->next;
	}
	printf("%s)\n%s", GREEN, RESET);
}

void	visit_tree(const t_tree_node *tree, size_t spaces)
{
	indent(spaces);
	if (tree->type == PIPE_NODE)
	{
		print_pipeline(tree->data.pipe, spaces);
	}
	else if (tree->type == CMD_NODE)
	{
		print_command(tree->data.cmd);
	}
}

void	print_tree(const t_tree_node *tree)
{
	printf("%s=============  ASTree =============%s\n\n", YELLOW, RESET);
	visit_tree(tree, 0);
	printf("\n%s===================================%s\n", YELLOW, RESET);
}
