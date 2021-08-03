#include <stdlib.h> //for getenv
#include <sys/stat.h> //for lstat
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "../../include/minishell.h"

char	*get_path(char *str)
{
	char		*path;
	char		*full_path;
	char		**paths;
	int			i;
	struct stat	buffer;

	path = getenv("PATH");
	paths = ft_split(path, ':');
	if (!paths)
		return (0);//error on split
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], str);
		if (lstat(full_path, &buffer) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		i++;
		free(full_path);
	}
	free_array(paths);
	return (0);
}

// int	execute_program(char **argument, char **envp)
// {
// 	char	*semi_path;
// 	char	*full_path;

// 	semi_path = ft_strjoin("/", argument[0]);
// 	full_path = get_path(semi_path);
// 	if (!full_path)
// 		return (-1);//error treatement
// 	free(argument[0]);
// 	free(semi_path);
// 	argument[0] = full_path;
// 	if (execve(argument[0], argument, envp) == -1)
// 		return (-1);
// 	return (0);
// }

int	execute_existing_program(char **argument, char **envp)
{
	char	*semi_path;
	char	*full_path;

	if (argument[0][0] != '/')
	{
		semi_path = ft_strjoin("/", argument[0]);
		full_path = get_path(semi_path);
		if (!full_path)
			return (-1);//error treatement
		free(argument[0]);
		free(semi_path);
		argument[0] = full_path;
	}
	if (execve(argument[0], argument, envp) == -1)
		return (-1);
	return (0);
}

