/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/13 22:00:25 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/13 22:00:27 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*temp;

	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		temp = (*tokens)->next;
		free((*tokens)->content);
		free(*tokens);
		*tokens = temp;
	}
	return ;
}

void	free_tree(t_tree_node *tree)
{
	if (!tree)
		return ;
	else if (tree->type == PIPE_NODE)
	{
		free_tree(tree->data.pipe.left);
		free_tree(tree->data.pipe.left);
	}
	else if (tree->type == CMD_NODE)
	{
		free_tokens(&(tree->data.cmd.tokens));
		free(tree);
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_array2(char **array, int n)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (i < n)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_var(t_pair_lst *var)
{
	if (!var)
		return ;
	free(var->key);
	free(var->value);
	free(var);
}
