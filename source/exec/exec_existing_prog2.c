/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_existing_prog2.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/15 11:21:18 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/15 11:21:20 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "../../include/minishell.h"
#include "../../include/built_in.h"

int	find_executable_path(char *semi_path, char *full_path, char ***argument)
{
	int			len;
	struct stat	buffer;

	len = ft_strlen(*argument[0]);
	if (len > 1 && (*argument)[0][0] == '.' && (*argument)[0][1] == '/')
	{
		semi_path = getcwd(NULL, 0);
		(*argument)[0] = ft_memmove(*argument[0], (*argument)[0] + 1, len - 1);
		(*argument)[0][len - 1] = '\0';
		full_path = ft_strjoin(semi_path, *argument[0]);
		if (lstat(full_path, &buffer) == 0)
		{
			free(*argument[0]);
			free(semi_path);
			*argument[0] = full_path;
		}
		else
		{
			free(semi_path);
			free(full_path);
			set_var("PIPESTATUS", "127");
			return (0);
		}
	}
	return (1);
}

void	free_pointers(char *str, char *ptr)
{
	if (!str)
		free(str);
	if (!ptr)
		free(ptr);
}

static int	result_check(int result, char **str,
			char *full_path, char *semi_path)
{
	struct stat	buffer;

	if (!result)
	{
		free_pointers(semi_path, full_path);
		set_var("PIPESTATUS", "127");
		return (0);
	}
	else
	{
		full_path = getcwd(NULL, 0);
		full_path = ft_strjoin(full_path, semi_path);
		if (lstat(full_path, &buffer) == 0)
		{
			free_pointers(*str, semi_path);
			*str = full_path;
			return (1);
		}
		else
		{
			set_var("PIPESTATUS", "127");
			free_pointers(semi_path, full_path);
			return (error_new_bool(*str, NULL, "command not found", 1));
		}
	}
}

int	treat_exec(char *semi_path, char ***argument, char *full_path)
{
	int	result;

	semi_path = ft_strjoin("/", *argument[0]);
	result = get_path(semi_path, &full_path);
	if (result == 0 || result == -1)
		return (result_check(result, &(*argument)[0], full_path, semi_path));
	free(*argument[0]);
	free(semi_path);
	*argument[0] = full_path;
	set_var("PIPESTATUS", SUCCESS);
	return (1);
}
