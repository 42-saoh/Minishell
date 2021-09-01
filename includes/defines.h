/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:05:24 by taesan            #+#    #+#             */
/*   Updated: 2021/09/01 19:33:58 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "minishell.h"

typedef struct s_sort
{
	int		idx_l;
	int		idx_r;
	int		idx_m;
	int		curr_l;
	int		curr_r;
	int		k;
}				t_sort;

typedef struct s_strjoin
{
	int		front_s;
	int		front_len;
	int		back_s;
	int		back_len;
	char	*front;
	char	*back;
	char	*content;
}				t_strjoin;

typedef struct s_data_to_temp
{
	int		read_fd;
	int		write_fd;
	char	*key;
	char	*param;
}				t_data_to_temp;

typedef struct s_info
{
	t_list	*commands;
	t_list	*commands_symbol;
	t_list	*redirect_lst;
	t_list	*param_list;
	t_list	*temp_list;
	void	(*sigint)(int);
	void	(*sigquit)(int);
	char	**paths;
	char	**param;
	char	**envp;
	char	*input;
	int		command_cnt;
	int		asterisk_check;
	int		is_builtin;
	int		envp_cnt;
	int		param_cnt;
	int		pipe_in[2];
	int		pipe_out[2];
	int		connect_pipe[2];
	int		redirect_fd[2];
	int		std_in;
	int		exec_result;
}				t_info;
/*
	constants
*/
# define INPUT_CHANGED 1
# define NOT_BUILTIN 0
# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7
# define SINGLE_Q '\''
# define DOUBLE_Q '\"'
# define PIPE '|'
# define DOLLAR '$'
# define REDIRECT_IN '<'
# define REDIRECT_OUT '>'
# define SG_PIPE 1
# define DB_PIPE 2
# define DB_AMPER 3
# define EXEC_FAIL 42
# define READ_FD_IDX 0
# define WRITE_FD_IDX 1
# define STDIN_PIPE 0x1
# define STDOUT_PIPE 0x2
# define BUFFER_SIZE 255
# define FD_MAX 255
# define PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# define SHELL_NAME "minishell"
/*
	program Error
*/
# define SPLIT_ERR "ft_split Error"
# define MALLOC_ERR "malloc Error"
# define WAIT_ERR "wait func return Error [-1]"
# define MAKE_NEW_INPUT_ERR "make new input Error"
# define FILTER_INPUT_ERR "filter_input error"
# define NOT_CLOSED "quotes are not closed"
# define PARSE_ERR "PARSING ERROR"
# define SPLIT_ERR "ft_split Error"
# define INPUT_OPEN_ERR "input file open"
# define FILE_OPEN_ERR "file open Error"
# define DUP2_ERR "dup2"
# define PIPE_ERR "create pipe Error"
# define UNLINK_ERR "file remove Error"
/* 
	bash Error 
*/
# define NO_SUCH_FILE "No such file or directory"
# define BAD_FD "Bad file descriptor"
# define UNEXPECTED_TOKEN "syntax error near unexpected token `&\'"
# define EXIT_NUMERIC_ERR "exit: -n: numeric argument required"
# define EXIT_MANY_ARGS "exit \nexit: too many arguments"
# define COMMAND_NOT_FOUND "command not found"
/*
	file names
*/
# define TEMP_FILE ".temp.txt"
# define EXPORT_FILE ".export.txt"
# define EXPORT_FILE_2 ".export_2.txt"
# define ENV_FILE ".env.txt"
# define ENV_FILE_2 ".env_2.txt"

#endif
