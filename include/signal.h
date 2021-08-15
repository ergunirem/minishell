/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/13 22:05:38 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/13 22:05:39 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "../include/minishell.h"
# include <signal.h>

void	handle_parent_signal(int sig);
void	handle_child_signal(int sig);
int		handle_ctrl_d(void);

#endif
