#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"
# include <stdbool.h>

bool	is_built_in(char *cmd);
bool	exec_built_in(char **args, int argc, char **envp);
bool	exec_pwd(void);
bool	exec_cd(char **arguments);

#endif
