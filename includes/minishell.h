#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "defines.h"

/*
	data_set.c
*/
char	**set_path(char *envp[]);
char	*get_env_value(char *envp[], char *input, int len);

/*
	error.c
*/
int		error_occur_std(char *msg);
int		error_occur_perror(char *msg);
/*
	utils
*/
int		is_quotation(char c);
/*
	check
*/
int		check_builtin(char *cmd);
char	*check_command(char **paths, char *cmd, int len);
int		exist_dollar(char *input, int s, int e);
/*
	readline
*/
void	wait_closing_quote(char start_q);
/*
	init
*/
int		init_info(t_info *info);
int		set_command_info(t_info *info, char *input);
/*
	using free
*/
void	split_free(char **data);
void	ft_free(void *data);
/*
	exec
*/
void	exec_command(t_info *info);
/*
	make command list
*/
int		make_command_list(t_info *info, char *input);
void	move_end_point(char *line, int *e, char end_c);
/*
	filter
*/
int	command_filter(t_info *info, char **content);
/*
	replace_env
*/
int		replace_env(char **envp, char **ptr, int s, int *next_idx);


#endif