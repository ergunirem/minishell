#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "minishell.h"

/* Scope of Variables in Shell
**
** Environment: The outermost scope is the environment.
** This is the only scope managed by the operating system.
** It is therefore guaranteed to exist for every process.
** When a process is started it receives a copy of its parent's environment.
** Modifying the child's environment does not change the parent's,
** modifying the parent's environment does not change that of an existing child.
**
** Shell Vars: When you assign a value to a variable in a shell,
** if the variable is not in the environment yet it becomes a shell variable.
** If it exists in the environment, environment var receives the new value.
** New value is only for the shell itself and its subsequently forked children.
** Shell variables only exist within the shell process.
** They are never inherited by child processes.
** There is a hierarchy of variable scopes, as expected.
** Export copies a shell variable into the shell process's environment,
** making it possible for child processes to inherit.
*/

typedef struct s_pair_lst
{
	char				*key;
	char				*value;
	struct s_pair_lst	*next;
}	t_pair_lst;

typedef struct s_env
{
	t_pair_lst	*env_vars;
	int			is_forked;
}	t_env;

extern t_env	g_env;

int			init_env_variables(char **envp);
int			add_env(char *envp);
t_pair_lst	*find_env_var(t_pair_lst *lst, char *var_name);
t_pair_lst	*create_key_value_pair(char *env_var);
void		set_var(char *key, char *value);
void		update_var(char *key, char *value);
void		remove_var(t_pair_lst **lst, char *key);
void		free_var(t_pair_lst *var);

#endif
