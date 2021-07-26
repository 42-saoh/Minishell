#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "defines.h"

/*
	data_set.c
*/
char	**set_path(char *envp[]);

/*
	error.c
*/
int		error_occur_std(char *msg);
int		error_occur_perror(char *msg);
/*
	utils
*/
void	jump_space(char **input);
char	*get_str(char **input);
/*
	check
*/
void	check_input(char *input, t_info *info);
int		check_builtin(char *cmd);
/*
	readline
*/
void	wait_closing_quote(char start_q);


#endif