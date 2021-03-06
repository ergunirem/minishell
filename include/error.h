/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/13 22:05:15 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/13 22:05:17 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>

# define SUCCESS "0"
# define GENERAL_ERROR "1"
# define SYNTAX_ERROR "2"
# define ENV_ERROR "127"

# define MALLOC_ERROR "malloc failed"
# define QUOTE_ERROR "unclosed quote"
# define NUMERIC_ERROR "numeric argument required"
# define PIPE_ERROR_MSG "syntax error near unexpected token `|'"
# define REDIR_ERROR_MSG "syntax error near unexpected token redirection"
# define MANY_ARG_ERR_MSG "too many arguments"
# define ID_ERR_MSG "not a valid identifier"

bool	error_msg(char *msg, char *error_code);
bool	error_new_bool(char *command, char *arg, char *msg, int fd);
int		error_new_int(char *command, char *arg, char *msg, int fd);
bool	lexer_error(t_token *new, char *msg, char *error_code);
char	**error_msg_inclfree(char *msg, char **argv, int argc);

#endif
