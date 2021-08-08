#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "../../include/minishell.h"

static int	get_path(char *str, char **full_path)
{
	char		*path;
	char		**paths;
	int			i;
	struct stat	buffer;

	path = getenv("PATH");
	paths = ft_split(path, ':');
	if (!paths)
		return (error_new_bool(NULL, NULL, strerror(errno), 1));
	i = 0;
	while (paths[i])
	{
		*full_path = ft_strjoin(paths[i], str);
		if (lstat(*full_path, &buffer) == 0)
		{
			free_array(paths);
			return (1);
		}
		i++;
		free(*full_path);
	}
	free_array(paths);
	return (-1);
}

int	check_existing_program(char ***argument, char **envp)
{
	char	*semi_path;
	char	*full_path;
	int		result;

	if (*argument[0][0] != '/')
	{
		semi_path = ft_strjoin("/", *argument[0]);
		result = get_path(semi_path, &full_path);
		if (!result)
			return (0);
		if (result == -1)
		{
			update_var("PIPESTATUS", "127");
			return (error_new_bool(*argument[0], NULL, "command not found", 1));
		}
		update_var("PIPESTATUS", SUCCESS);
		free(*argument[0]);
		free(semi_path);
		*argument[0] = full_path;
	}
	return (1);
}
