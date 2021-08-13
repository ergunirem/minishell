/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/06 11:58:03 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/12 11:50:41 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
**	Count token number until pipe for sublist and
**	Change the head of the list to the next token after pipe
*/
t_token	*sublist_until_pipe(t_token **tokens, int count)
{
	t_token	*sublist_head;
	t_token	*sublist;

	sublist = (*tokens);
	while ((*tokens))
	{
		if ((*tokens)->type == CHAR_PIPE)
		{
			(*tokens) = (*tokens)->next;
			break ;
		}
		count++;
		(*tokens) = (*tokens)->next;
	}
	sublist_head = sublist;
	while (sublist)
	{
		count--;
		if (count == 0)
			break ;
		sublist = sublist->next;
	}
	sublist->next = NULL;
	return (sublist_head);
}

t_tree_node	*parse_command(t_token **tokens)
{
	t_tree_node	*new_node;

	new_node = malloc(sizeof(t_tree_node));
	if (!new_node)
		return (NULL);
	new_node->type = CMD_NODE;
	new_node->data.cmd.tokens = sublist_until_pipe(tokens, 0);
	return (new_node);
}

t_tree_node	*create_pipe_node(t_tree_node *left, t_tree_node *right)
{
	t_tree_node	*new_node;

	new_node = malloc(sizeof(t_tree_node));
	if (!new_node)
		return (NULL);
	new_node->type = PIPE_NODE;
	new_node->data.pipe.left = left;
	new_node->data.pipe.right = right;
	return (new_node);
}

t_tree_node	*parse_pipe(t_token **tokens)
{
	t_tree_node	*left;
	t_tree_node	*right;

	g_env.pipe_exit = 1;
	left = parse_command(tokens);
	right = parser(tokens);
	return (create_pipe_node(left, right));
}

t_tree_node	*parser(t_token **tokens)
{
	int	peek;

	peek = peak_ahead(*tokens);
	if (peek == PIPE_NODE)
		return (parse_pipe(tokens));
	else
		return (parse_command(tokens));
}
