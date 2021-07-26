#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>

# define PIPE_ERROR_MSG "syntax error near unexpected token `|'\n"
# define REDIR_ERROR_MSG "syntax error near unexpected token redirection\n"
# define ENV_ERR_MSG "env: too many arguments"
# define IDENTIFIER_ERR_MSG "not a valid identifier"

bool	error_new_bool(char *command, char *arg, char *msg, int fd);
int		error_new_int(char *command, char *arg, char *msg, int fd);

#endif
