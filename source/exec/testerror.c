#include <string.h>
#include <stdio.h>

int main()
{
	int i;

	i = 0;
	while (i < 100)
	{
		printf("%s\n",strerror(i));
		i++;
	}
	return (0);
}