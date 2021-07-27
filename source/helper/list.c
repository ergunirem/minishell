#include "../../include/minishell.h"

t_token	*ft_listlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_listadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (new && *lst)
	{
		last = ft_listlast(*lst);
		last->next = new;
		new->next = NULL;
	}
	else if (!*lst)
	{
		*lst = new;
		new->next = NULL;
	}
}
