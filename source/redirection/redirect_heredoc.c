#include "../../include/minishell.h"

static int	str_cmp(char *str1, char *str2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);

	if (len1 != len2)
		return (-1);
	else
		return (ft_memcmp(str1, str2, len1));
}

int	exec_heredoc(t_token *token, char *file, t_context *ctx, int count)
{
	char	*delimiter;
	char	*newline;
	int		len;
	int		len_nl;
	int		fd[2];

	delimiter = ft_strdup(token->next->content);
	printf("delimiter is %s\n", delimiter);
	len = ft_strlen(delimiter);
	// if ((delimiter[0] == '\'' && delimiter[len - 1] == '\'') || (delimiter[0] == '\"' && delimiter[len - 1] == '\"'))
	// {
	// 	if(ft_strrchr(file, '$'))//expansion
	// 		file = expand_param(file);
	// }
	if (pipe(fd) == -1)
		return (-1); //error as pipe error
	newline = readline("<");
	while (str_cmp(delimiter, newline) != 0)
	{
		len_nl = ft_strlen(newline);
		write(fd[1], newline, len_nl);
		write(fd[1], "\n", 1);
		free(newline);
		newline = readline("<");
	}
	free(newline);
	close(fd[1]);
	return (fd[0]);
}
