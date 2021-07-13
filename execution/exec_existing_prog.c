#include <stdlib.h> //for getenv
#include <sys/stat.h> //for lstat
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "minishell.h"

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

int	execute_program(char **argument, char **envp)
{
	char	*semi_path;
	char	*full_path;

	semi_path = ft_strjoin("/", argument[0]);
	full_path = get_path(semi_path);
	if (!full_path)
		return (-1);//error treatement
	free(argument[0]);
	free(semi_path);
	argument[0] = full_path;
	if (execve(argument[0], argument, envp) == -1)
		return (-1);
	return (0);
}

// void	redirection(char *redirect_in, char *redirect_out)
// {
// 	int	redirect_out_fd;
// 	int	redirect_in_fd;

// 	redirect_out_fd = open(redirect_out, O_CREAT | O_TRUNC | O_WRONLY); //depends on double or single > (output redirection to see if use flag TRUNC)
// 	redirect_in_fd = open(redirect_in, O_CREAT | O_TRUNC | O_RDONLY); //depends on double or single > (output redirection to see if use flag TRUNC)
// 	if (redirect_out_fd)//error check
// 	dup2(redirect_out_fd, STDOUT_FILENO);//need to add error check
// 	dup2(redirect_in_fd, STDIN_FILENO);//need to add error check
// 	close(redirect_out_fd);//error check on close call
// 	close(redirect_in_fd);//error check on close call
// }
