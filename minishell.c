#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

/* compile gcc -Wall -Wextra -Werror -lreadline test_shell.c && ./a.out */

static volatile sig_atomic_t	keep_running = 1;

void	inthandler(int _)
{
	(void)_;
	keep_running = 0;
}

int	main(void)
{
	int		pid;
	int		s_wait;
	char	*line;
	char	**array;

	pid = fork();
	if (pid < 0)
		ft_error();//to add the error handling function
	if (pid == 0)
	{
		signal(SIGINT, inthandler);
		while (keep_running)
		{
			line = readline("Minishell$");
			if (line)
				printf("%s\n", line);
			/*steps for main function
			{
				parsing(line, array);//to add parsing
				check_input(array);//to add check input
				command_handle(array);//to handle different commands
			}
			*/
		}
	}
	else
	{
		wait(&s_wait);
		return (0);
	}
}
