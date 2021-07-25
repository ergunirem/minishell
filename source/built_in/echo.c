#include "../../include/built_in.h"

size_t	check_n_option(char *str)
{
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

/*
echo utility writes any specified operands, separated by single blank (` ')
and followed by a newline (`\n') character, to the standard output (fd = 1)
*/

int	exec_echo(char **args, int argc, t_context *ctx)
{
	size_t	i;
	size_t	n_option;

	i = 1;
	n_option = 0;
	//variable display?
	while (args[i] && args[i][0] == '-')
	{
		if (check_n_option(args[i] + 1) == 0)
			break ;
		n_option++;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], ctx->fd[1]);
		if (i != argc - 1)
			ft_putstr_fd(" ", ctx->fd[1]);
		i++;
	}
	if (n_option == 0)
		ft_putstr_fd("\n", ctx->fd[1]);
	return (0);
}
