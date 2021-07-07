#include "minishell.h"
#include "parser.h"

int	peak_ahead(t_token *tokens)
{
	if (!tokens)
		return (-1)
	while (tokens)
	{
		if (tokens->type == CHAR_PIPE)
			return (2);
		tokens = tokens->next;
	}
	return (1);
}

t_token	*sublist_until_pipe(t_token **tokens)
{
	t_token	*new_sublist_head;
	t_token	*new_sublist;
	int		count;

	new_sublist = (*tokens);
	new_sublist_head = (*tokens);
	// lst_print(tokens);
	count = 0;
	//count token number until pipe for sublist and
	//change the head of the list to the next token after pipe
	while((*tokens))
	{
		//when there is no pipe?
		if((*tokens)->type == CHAR_PIPE || (*tokens)->next == NULL)
		{
			(*tokens) = (*tokens)->next;
			break ;
		}
		count++;
		(*tokens) = (*tokens)->next;
	}
	while(new_sublist)
	{
		if(count == 0)
		{
			new_sublist->next = NULL;
			return (new_sublist_head);
		}
		count--;
		new_sublist = new_sublist->next;
	}
}

t_tree_node	*parse_command(t_token *tokens)
{
	t_tree_node	*new_node;

	new_node = malloc(sizeof(t_tree_node));
	if (!new_node)
		return (NULL);
	new_node->type = CMD_NODE;
	new_node->data.cmd.tokens = sublist_until_pipe(&tokens);
	return (new_node);
}

t_tree_node *create_pipe_node(t_tree_node *left, t_tree_node *right)
{
	t_tree_node	*new_node;

	//check if left and right are null?
	new_node = malloc(sizeof(t_tree_node));
	if (!new_node)
		return (NULL);
	new_node->type = PIPE_NODE;
	new_node->data.pipe.left = left;
	new_node->data.pipe.right = right;
	return (new_node);
}

t_tree_node	*parse_pipe(t_token *tokens)
{
	t_tree_node	*left;
	t_tree_node	*right;
	int			peek;

	left = parse_command(tokens); //change the head of the list to the next token after pipe
	peek = peak_ahead(tokens);
	if (peek == PIPE)
		right = parse_pipe(tokens);
	else //do I need error?
		right = parse_command(tokens);
	return(create_pipe_node(left, right));
}

t_tree_node	*parser(t_token *tokens)
{
	int	peek;

	peek = peak_ahead(tokens);
	if (peek == 2)
		return (parse_pipe());
	else if (peek == 1)
		return (parse_command());
	// else
	// 	return (error_node());
}
