#include "../includes/minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	char *s;
	int i = 0;

	while(i < 3)
	{
		s = readline("my minishell : ");
		add_history(s);
		printf("%s\n", s);
		i++;
	}
}