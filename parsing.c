#include "minishell.h"

t_ASTtree	*create_tree_node(void)
{
	t_ASTtree	*new;

	new = malloc(sizeof(t_ASTtree));
	if (!new)
		return (NULL);
	new->left = NULL;
	new->right = NULL;
	new->content = NULL;
	new->type = 0;
	return (new);
}

t_token	*find_pipe(t_token *tokens)
{
	printf("pipe-in!\n");
	// lst_print(tokens);
	while(tokens)
	{
		if(tokens->type == CHAR_PIPE)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

//This part ignored >'s and was based on the idea that tokens go like this:
//cmd + cmd_suffix
void	handle_no_pipe(t_ASTtree *tree, t_token *tokens)
{
	t_ASTtree *tree_node1;
	t_ASTtree *tree_node2;

	printf("no-pipe-in!\n");
	tree_node1 = create_tree_node();
	if(!tree_node1)
		exit(0);
	tree = tree_node1;
	tree->type = CMD_LINE;
	tree->content = ft_strdup(tokens->content);
	printf("t:%d c:%s\n", tree->type, tree->content);
	//move on to the next token which should be suffix?
	tree_node2 = create_tree_node();
	if(!tree_node2)
		exit(0);
	tree->left = tree_node2;
	tree->left->type = WORD;
	tree->left->content = ft_strdup(tokens->next->content);
	printf("t:%d c:%s\n", tree->left->type, tree->left->content);
}

void	handle_with_pipe(t_ASTtree *tree, t_token *tokens, t_token *pipe)
{
	printf("pipe-in!\n");
	tree = create_tree_node();
	if(!tree)
		exit(0);
	tree->type = PIPE;
	printf("t:%d c:%s\n", tree->type, tree->content);
	handle_no_pipe(tree->left, tokens);
	//previous pipe part is erased from the tokens list
	tokens = pipe->next;
	pipe = find_pipe(tokens);
	if (pipe)
		handle_with_pipe(tree->right, tokens, pipe);
	else
		return ;
}

/*
First ignore $ARG or >test.txt and save everything as if
first element is the command and rest is words.
*/

void	parser(t_token *tokens, t_ASTtree **tree)
{
	t_token *beginning;
	t_token *pipe;

	// *tree = create_tree_node();
	// if(!tree)
	// 	exit(0);
	pipe = find_pipe(tokens);
	printf("pipe:%p\n", pipe);
	if (pipe)
		handle_with_pipe(*tree, tokens, pipe);
	else
		handle_no_pipe(*tree, tokens);
}


//IDEA BEHIND RECURSION

//check first for a pipe
	//pipe: traverse from leftest till pipe & create tree

	//no pipe:just save the words
