#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "../../include/minishell.h"

static int	get_path(char *str, char **full_path)
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

static int	get_argument(char *str)
{
	int			i;
	t_pair_lst	*env_var;
	char		**paths;
	struct stat	buffer;

	i = 0;
	env_var = find_env_var(g_env.env_vars, "PATH");
	if (!env_var)
		return (-1);
	paths = ft_split(env_var->value, ':');
	if (!paths)
		return (error_new_bool(NULL, NULL, strerror(errno), 1));
	while (paths[i])
	{
		if (lstat(str, &buffer) == 0)
		{
			free_array(paths);
			return (1);
		}
		i++;
	}
	free_array(paths);
	return (-1);
}

static int	result_check(int result, char *str)
{
	if (!result)
	{
		set_var("PIPESTATUS", "127");
		return (0);
	}
	else
	{
		set_var("PIPESTATUS", "127");
		return (error_new_bool(str, NULL, "command not found", 1));
	}
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
		if (result == 0 || result == -1)
			return (result_check(result, *argument[0]));
		free(*argument[0]);
		free(semi_path);
		*argument[0] = full_path;
	}
	else
	{
		if (get_argument(*argument[0]) == -1)
		{
			set_var("PIPESTATUS", "127");
			return (error_new_bool(*argument[0],
					NULL, "No such file or directory", 1));
		}
	}
	set_var("PIPESTATUS", SUCCESS);
	return (1);
}
