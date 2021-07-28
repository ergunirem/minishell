#ifndef PARSER_H
# define PARSER_H
# include "token.h"

/* Grammar > production rules
** TREE_NODE	:: = CMD_NODE OR PIPE_NODE
** CMD_NODE		:: = LIST OF TOKENS
** PIPE_NODE	:: = TREE_NODE (LEFT=ALWAYS CMD) AND TREE_NODE (RIGHT=PIPE OR CMD)
*/

/* Example: < infile cat -e | wc | cat -e > outfile

										tree_node : type=pipe
				┌─(tree_node->data.pipe.left)─────┴──────(tree_node->data.pipe.right)─┐
	  tree_node : type=cmd													tree_node : type=pipe
			↓											┌─(tree_node->data.pipe.left)─┴─(tree_node->data.pipe.right)─┐
		token(content="<")						tree_node:type=cmd											tree_node:type=cmd
			↓											↓															↓
		token(content="infile")					token(content="wc")											token(content="cat")
			↓																										↓
		token(content= "cat")																				token (content="-e")
			↓																										↓
		token(content= "-e")																				token (content=">")
																													↓
																											token (content="outfile")
*/

typedef enum e_node_type{
	CMD_NODE = 1,
	PIPE_NODE = 2,
} t_node_type;

typedef struct s_pipe_node
{
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_pipe_node;

typedef struct s_cmd_node
{
	t_token	*tokens;
}	t_cmd_node;

typedef union s_node_value
{
	t_pipe_node	pipe;
	t_cmd_node	cmd;
} t_node_value;

typedef struct s_tree_node
{
	t_node_type		type;
	t_node_value	data;
} t_tree_node;

bool		check_list(t_token *tokens);
t_tree_node	*parser(t_token **tokens);
int			peak_ahead(t_token *tokens);
void		print_tree(const t_tree_node *tree);
void		free_tree(t_tree_node *tree);
void		visit_tree(const t_tree_node *tree, size_t spaces);

#endif
