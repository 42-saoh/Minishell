#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main()
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
