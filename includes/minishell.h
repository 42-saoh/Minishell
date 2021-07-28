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
int		check_builtin(char *cmd);
char	*check_command(char **paths, char *cmd, int len);
/*
	readline
*/
void	wait_closing_quote(char start_q);
/*
	init
*/
int		init_info(t_info *info, char *input, char *envp[]);
/*
	using free
*/
void	split_free(char **data);
/*
	input filter
*/
char	*input_space_filter(char *input);


#endif