#include "../../include/minishell.h"

int	main(int argc, char **argv)
{
	char	*line;
	char	*delimiter;
	int		fd[2];
	int		len;
	char	buf[1000];

	if (argv[1][0] == '<' && argv[1][1] == '<')
	{
		if (!argv[1][2])
			return (-1);
		else
			delimiter = strdup(argv[1] + 2);
	}
	len = strlen(delimiter);
	line = readline(">");
	pipe(fd);
	while (memcmp(line, delimiter, len) != 0)
	{
		free(line);
		len = strlen(line);
		write(fd[1], line, len);
		write(fd[1], "\n", 1);
		line = readline(">");
	}
	free(line);
	close (fd[1]);
	len = read(fd[0], buf, 1000);
	printf("%s", buf);
}