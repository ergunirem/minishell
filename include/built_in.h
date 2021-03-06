/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/13 22:05:04 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/14 14:31:01 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "environment.h"
# include <stdbool.h>

typedef struct s_context
{
	int			fd[3];
	int			fd_close;
	int			*redir;
}				t_context;

bool			is_built_in(char *cmd);
int				exec_built_in(char **args, int argc,
					t_context *ctx, char **envp);
int				exec_pwd(t_context *ctx);
int				exec_cd(char **arguments, t_context *ctx);
int				exec_env(char **args, int argc, t_context *ctx);
int				exec_export(char **args, int argc, t_context *ctx);
int				exec_unset(char **args, int argc, t_context *ctx);
int				exec_echo(char **args, int argc, t_context *ctx);
int				exec_exit(char **args, int argc, t_context *ctx);
int				redirection(t_token **token, t_context *ctx, int count);
int				count_redirection(t_token *token, t_context *ctx);
int				exec_heredoc(t_token *token, t_context *ctx, int count);
int				exec_command(t_tree_node *node, t_context *ctx, char **envp);
int				exec_pipe(t_tree_node *node, t_context *ctx, char **envp);
int				exec_node(t_tree_node *node, t_context *ctx, char **envp);
int				count_node(t_token *token);
void			close_redirection(int *fd, int count);
int				free_set(char **argv, t_context *ctx, int argc, int n);
int				check_complexcmd(char ***argv, int *argc);
int				treat_exec(char *semi_path, char ***argument, char *full_path);
int				find_executable_path(char *semi_path,
					char *full_path, char ***argument);
int				get_path(char *str, char **full_path);

#endif
