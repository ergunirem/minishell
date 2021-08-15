/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_existing_prog.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/13 22:03:22 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/14 14:32:17 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "../../include/minishell.h"

/* returns the path which has the executable 
- return 0 when there is malloc error
- return -1 when cannot find path
- return 1 when find the path
*/
int	get_path(char *str, char **full_path)
{
	t_pair_lst	*env_var;
	char		**paths;
	int			i;
	struct stat	buffer;

	env_var = find_env_var(g_env.env_vars, "PATH");
	if (!env_var)
		return (-1);
	paths = ft_split(env_var->value, ':');
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

/*check if within given argument (absolute path) the executable indeed exist */
static int	get_argument(char ***argument)
{
	int			i;
	struct stat	buffer;

	i = 0;
	while ((*argument)[0][i])
	{
		if (ft_iswhitespace((*argument)[0][i]) == 1)
			break ;
		i++;
	}
	(*argument)[0][i] = '\0';
	if (lstat((*argument)[0], &buffer) == 0)
		return (0);
	else
		return (-1);
}

int	count_slash(char *str)
{
	int	len;
	int	i;
	int	count_slash;

	len = ft_strlen(str);
	i = 0;
	count_slash = 0;
	while (i < len)
	{
		if (str[i] == '/')
			count_slash++;
	}
	return (count_slash);
}

int	check_existing_program(char ***argument, char **envp)
{
	char		*semi_path;
	char		*full_path;
	struct stat	buffer;

	if (*argument[0] == NULL)
		return (0);
	if ((*argument)[0][0] == '\0')
	{
		set_var("PIPESTATUS", "127");
		return (error_new_bool("\0", NULL, "command not found", 1));
	}
	if (((*argument)[0][0] == '.') &&
		(!find_executable_path(semi_path, full_path, argument)))
		return (error_new_bool(*argument[0],
				NULL, "No such file or directory", 1));
	else if (*argument[0][0] != '/')
		return (treat_exec(semi_path, argument, full_path));
	else if (get_argument(argument) == -1)
	{
		set_var("PIPESTATUS", "127");
		return (error_new_bool(*argument[0],
				NULL, "No such file or directory", 1));
	}
	set_var("PIPESTATUS", SUCCESS);
	return (1);
}
