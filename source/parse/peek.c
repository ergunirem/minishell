#include "../../include/minishell.h"

int	peak_ahead(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == CHAR_PIPE)
			return (2);
		tokens = tokens->next;
	}
	return (1);
}
