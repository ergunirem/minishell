/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/07 22:05:07 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/10 17:13:31 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signal.h"
#include <stdio.h>

/*
**	if ctrl-\ (SIGQUIT) is received
		regenerates the prompt
		displays readline again to receive input
**	if ctrl-c (SIGINT) is received,
		moves to a new line, regenerates the prompt on a newline
		clears the previous text, displays readline again to receive input.
*/
void	handle_parent_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		set_var("PIPESTATUS", "0");
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGINT)
	{
		set_var("PIPESTATUS", "1");
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

/*
**	if ctrl-c (SIGINT) is received, no new prompt.
**	it's already done by the parent process's handle.
*/
void	handle_child_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		set_var("PIPESTATUS", "131");
	}
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		set_var("PIPESTATUS", "130");
	}
}

int	handle_ctrl_d(void)
{
	ft_putstr_fd("exit\n", 2);
	exit(0);
}
