#include "../../include/built_in.h"

bool	exec_pwd(void)
{
	char	*path;

	printf("PWD\n");
	path = getcwd(NULL, 0);
	if (!path)
		return (error_msg(PWD_ERROR_MSG));
	ft_putstr_fd(path, 0);
	ft_putstr_fd("\n", 0);
	free(path);
	return (true);
}

bool	exec_cd(char **arguments)
{
	char	*path;

	//change the pwd env variable as well!!
	//write this part after you have a working export func
	//change_pwd()?;
	if (chdir(arguments[1]) == -1)
		return (error_msg(CD_ERROR_MSG));
	return (true);
}
