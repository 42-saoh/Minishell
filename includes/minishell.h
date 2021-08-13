#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include "../libft/libft.h"
# include "defines.h"

/*
	error.c
*/
int		error_occur_std(char *msg);
int		error_occur_perror(char *msg);
/*
	utils
*/
int		is_quotation(char c);
int		pass_possible(char c);
int		is_empty(char *temp);
int		is_redirect(char c);
void	ft_close(int fd);
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
int		init_command_info(t_info *info, char *input);
char	**init_path(char *envp[]);
/*
	using free
*/
void	split_free(char **data);
void	ft_free(void *data);
/*
	exec
*/
void		exec_call(t_info *info, int instruct_seq);
/*
	make command list
*/
int		make_command_list(t_info *info, char *input);
/*
	filter
*/
int	command_filter(t_info *info, char **content);
int	redirect_filter(t_info *info, char **content);
/*
	replace_env
*/
int		replace_env(char **envp, char **ptr, int s, int *next_idx);

/*
	redirect util
*/
int		remove_redirect(int s, int e, char **content);

/*
	gnl
*/
int		get_next_line(int fd, char **line);
char	*content_null(char *buf);
char	*check_first(int fd, char **line);
/*
	test. 지워야 함
*/
void	command_to_string(t_info info);
/*
	sig_handler
*/
void	sigquit_handler(int signo);
void	sigint_handler(int signo);
/*
	set_connect_pipe
*/
int		set_connect_pipe(t_info *info, int seq);


#endif