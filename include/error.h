#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>

# define PIPE_ERROR_MSG "syntax error near unexpected token `|'\n"
# define REDIR_ERROR_MSG "syntax error near unexpected token redirection\n"
# define PWD_ERROR_MSG "pwd: getcwd failed\n"
# define CD_ERROR_MSG "cd: chdir failed\n"
# define ENV_ERR_MSG "env: too many arguments\n"
# define UNSET_ERR_MSG "not a valid identifier\n"

bool	error_new(char *command, char *arg, char *msg);

#endif