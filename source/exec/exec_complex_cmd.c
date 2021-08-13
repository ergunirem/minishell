#include "../../include/minishell.h"
#include "../../include/built_in.h"

int	count_whitespace(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && str[i + 1])
	{
		if (ft_iswhitespace(str[i]) && !ft_iswhitespace(str[i + 1]))
			count++;
		i++;
	}
	// printf("count is %d\n", count);
	if (ft_iswhitespace(str[0]) && i == 0)
		return (-1);//env is only white space =>should only pomp a new line
	else if (ft_iswhitespace(str[0]))
		return (count - 1);
	else
		return (count);
}

void	parse_nonwhitesp(char *str, char **argv, int *k)
{
	int	i;
	int	len;

	i = 0;
	while (str[i])
	{
		if ((i == 0 && (!ft_iswhitespace(str[i]))) || (!ft_iswhitespace(str[i]) && i > 0 && ft_iswhitespace(str[i - 1])))
		{
			len = 0;
			while (str[i + len])
			{
				if (!ft_iswhitespace(str[i + len]) && (!str[i + len + 1] || ft_iswhitespace(str[i + len + 1])))
				{
					argv[*k] = ft_substr(str, i, len + 1);
					// printf("argv %d is %s i is %d len is %d\n", *k, argv[*k], i, len);
					(*k)++;
					break;
				}
				len++;
			}
			i = i + len;
		}
		i++;
	}
}

int	check_complexcmd (char ***argv, int *argc)
{
	int	i;
	int	j;
	int	k;
	char **argv2;

	i = count_whitespace((*argv)[0]);
	if (i == -1)
		return (0);
	if (i == 0)
		return (1);
	j = 0;
	argv2 = malloc((argc[0] + 1 + i) * sizeof(char *));
	if (!argv2)
		return (error_new_bool(NULL, NULL, strerror(errno), 2));
	argv2[argc[0] + i] = NULL;
	parse_nonwhitesp((*argv)[0], argv2, &j);
	// printf("j is %d and i is %d\n", j, i);
	while (j < argc[0] + 1 + i)
	{
		argv2[j] = ft_strdup((*argv)[j - i]);
		// printf("argv2 %d is %s\n", j, argv2[j]);
		j++;
	}
	free_array(*argv);
	*argv = argv2;
	return (1);
}