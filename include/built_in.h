#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "environment.h"
# include <stdbool.h>

typedef struct	s_context{
	int	fd[3];
	int fd_close;
}	t_context;

bool	is_built_in(char *cmd);
bool	exec_built_in(char **args, int argc, t_context *ctx, char **envp);
int		exec_pwd(t_context *ctx);
int		exec_cd(char **arguments, t_context *ctx);
int		exec_env(char **args, int argc, t_context *ctx);
int		exec_export(char **args, int argc, t_context *ctx);
int		exec_unset(char **args, int argc, t_context *ctx);
int		exec_echo(char **args, int argc, t_context *ctx);
int		exec_exit(char **args, int argc, t_context *ctx);

#endif
