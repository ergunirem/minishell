#include "minishell.h"

/* added makefile and .h file to my version to compile easily */
/* added add_history and exit logic */
/* just to try dividing input by space and introduce basic tokenizer I used ft_split */

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
	t_token	*tokens;

	pid = fork();
	// if (pid < 0)
	// 	ft_error();//to add the error handling function
	if (pid == 0)
	{
		signal(SIGINT, inthandler);
		while (keep_running)
		{
			line = readline("Minishell$ ");
			if (ft_strlen(line) > 0)
				add_history(line);
			if (!ft_strncmp(line, "exit", 5))
			{
				free_tokens(tokens);
				break;
			}
			lexer(line, &tokens);
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
