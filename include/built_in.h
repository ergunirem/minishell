#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"
# include "environment.h"
# include <stdbool.h>

typedef struct	s_context{
	int	fd[2];
	int fd_close;
}	t_context;

bool	is_built_in(char *cmd);
bool	exec_built_in(char **args, int argc, t_context *ctx, char **envp);
int		exec_pwd(t_context *ctx);
bool	exec_cd(char **arguments);
int		exec_env(char **args, int argc);
int		exec_export(char **args, int argc);
int		exec_unset(char **args, int argc);

#endif
