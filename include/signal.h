#ifndef SIGNAL_H
# define SIGNAL_H

#include "../include/minishell.h"
#include <signal.h>

void	handle_parent_signal(int sig);
void	handle_child_signal(int sig);
int		handle_ctrl_d(void);

#endif
