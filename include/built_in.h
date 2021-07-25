#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"
# include "environment.h"
# include <stdbool.h>

bool	is_built_in(char *cmd);
bool	exec_built_in(char **args, int argc, char **envp);
int		exec_pwd(void);
bool	exec_cd(char **arguments);
int		exec_env(char **args, int argc);
int		exec_export(char **args, int argc);
int		exec_unset(char **args, int argc);
int		exec_echo(char **args, int argc);
int		exec_exit(char **args, int argc);

#endif
