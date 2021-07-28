#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>

# define MALLOC_ERROR "malloc failed"
# define QUOTE_ERROR "unclosed qoute"
# define PIPE_ERROR_MSG "syntax error near unexpected token `|'"
# define REDIR_ERROR_MSG "syntax error near unexpected token redirection"
# define ENV_ERR_MSG "env: too many arguments"
# define IDENTIFIER_ERR_MSG "not a valid identifier"

bool	error_msg(char *msg);
bool	error_new_bool(char *command, char *arg, char *msg, int fd);
int		error_new_int(char *command, char *arg, char *msg, int fd);
bool	lexer_error(t_token **tokens, char *msg);

#endif
