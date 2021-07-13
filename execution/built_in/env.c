#include "built_in.h"

/*
**	Returns error if env is called with other arguments.
*/

int	exec_env(char **args, int argc)
{
	if(argc != 1)
		return (error_msg(ENV_ERR_MSG));
}
