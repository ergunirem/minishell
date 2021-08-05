#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>

# define GENERAL_ERROR 1
# define SYNTAX_ERROR "2"
# define INCORRECT_USAGE 2
# define ENV_ERROR 127

# define MALLOC_ERROR "malloc failed"
# define QUOTE_ERROR "unclosed quote"
# define PIPE_ERROR_MSG "syntax error near unexpected token `|'"
# define REDIR_ERROR_MSG "syntax error near unexpected token redirection"
# define ENV_ERR_MSG "env: too many arguments"
# define IDENTIFIER_ERR_MSG "not a valid identifier"

bool	error_msg(char *msg, char *error_code);
bool	error_new_bool(char *command, char *arg, char *msg, int fd);
int		error_new_int(char *command, char *arg, char *msg, int fd);
bool	lexer_error(t_token *new, char *msg, char *error_code);

#endif
