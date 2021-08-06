#include "../include/signal.h"

/*
**	if detect [ctrl-c] during terminal input:
**	---- dis-regard previous input (clear buf), give a new prompt.
*/
// void	handle_parent_signal(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		ft_putstr_fd("\n", 2);
// 	}
// }

/*
**	if detect [ctrl-c] during child process:
**	---- no new prompt print as it's been done by parent process.
*/
// void	handle_child_signal(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		g_env.prompt.ctrl_c = 1;
// 	}
// }
