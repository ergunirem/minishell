/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/07 22:05:07 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/08/09 15:56:07 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signal.h"
#include<stdio.h>

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
	// write(1, &g_env.is_forked, 1);
	printf(">%d|", g_env.is_forked);
	if (sig == SIGQUIT)
	{
		update_var("PIPESTATUS", "131");
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGINT)
	{
		// ft_putstr_fd("CHILD\n", 1);

		update_var("PIPESTATUS", "130");
		ft_putstr_fd("\n", 1);
		// 		write(1, "\b\b", 2); // move cursor behind of ^C
		// write(1, "  ", 2);	 // remove ^C by printing spaces.
		// write(1, "\b\b", 2); // reset cursor pos
		rl_replace_line("", 1);

		rl_on_new_line();
		rl_redisplay();
	}
	// if (sig == SIGINT && g_env.is_forked == 1)
	// {
	// 	// update_var("PIPESTATUS", "130");
	// 	ft_putstr_fd("CHILD\n", 1);
	// 	// rl_replace_line("", 1);
	// 	// rl_on_new_line();
	// 	// rl_redisplay();
	// }
}

/*
**	if ctrl-c (SIGINT) is received, no new prompt.
**	it's already done by the parent process's handle.
*/
void	handle_child_signal(int sig)
{
	int i;

	// ft_putstr_fd("CHILD\n", 1);
	i = 0;
}

int	handle_ctrl_d(void)
{
	ft_putstr_fd("logout\n", 2);
	exit(0);
}
