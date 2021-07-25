#include "../../include/built_in.h"

int	check_numeric(char *str)
{
	size_t	i;

	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	exec_exit(char **args, int argc, t_context *ctx)
{
	int	exit_code;

	//exit_code to be reach everywhere?
	exit_code = 0;
	if (argc > 2)
	{
		exit_code = error_new_int("exit", NULL, "too many arguments", ctx->fd[2]);
		return (exit_code);
	}
	if(args[1])
	{
		if (!check_numeric(args[1])) //bash still logs out!
		{
			error_new_int("exit", NULL, "numeric argument required", ctx->fd[2]);
			exit_code = 2; //use macro - specific codes for errors?
		}
		if (exit_code != 2)
			exit_code = ft_atoi(args[1]);
	}
	//free_all?
	ft_putstr_fd("exit\n", ctx->fd[2]);
	exit(exit_code % 256);
}
