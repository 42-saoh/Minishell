/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:05:24 by taesan            #+#    #+#             */
/*   Updated: 2021/08/30 14:50:58 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

#include "minishell.h"

typedef	struct	s_sort
{
	int		idx_l;
	int		idx_r;
	int		idx_m;
	int		curr_l;
	int		curr_r;
	int		k;
}				t_sort;

typedef struct	s_strjoin
{
	int		front_s;
	int		front_len;
	int		back_s;
	int		back_len;
	char	*front;
	char	*back;
	char	*content;
}				t_strjoin;

typedef	struct	s_data_to_temp
{
	int		read_fd;
	int		write_fd;
	char	*key;
	char	*param;
}				t_data_to_temp;
/*
	명령어에서 아래 문자들이 존재하는지 ..
	single, double모두 존재할 경우, 1번이 먼저 나옴.
*/
typedef struct s_info
{
	t_list	*commands; // 마지막에 clear
	t_list	*commands_symbol; // 마지막에 clear
	t_list	*redirect_lst; // exec하고 clear
	t_list	*param_list;
	t_list	*temp_list;
	void	(*sigint)(int);
	void	(*sigquit)(int);
	char	**paths; // 계속 씀.
	char	**param; // parents에서 free됨.
	char	**envp; // 계속 씀.
	int		command_cnt; // 유동적.
	int		asterisk_check; // 유동적
	int		is_builtin; // param만들면서 체크 함.
	int		envp_cnt;
	int		param_cnt;
	int		pipe_in[2];
	int		pipe_out[2];
	int		connect_pipe[2];
	int		redirect_fd[2];
	int		std_in;
	int		exec_result; // exec하고 init
}				t_info;

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


# define PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# define SPLIT_ERR "ft_split Error"
# define MALLOC_ERR "malloc Error"
# define WAIT_ERR "wait func return Error [-1]"
# define SUBSTR_ERR "ft_substr Error"
# define STRJOIN_ERR "ft_strjoin Error"
# define MAKE_NEW_INPUT_ERR "make new input Error"
# define FILTER_INPUT_ERR "filter_input error"
# define NOT_CLOSED "quotes are not closed"
/*
	pipex defines ...ref..
*/

# define READ_FD_IDX 0
# define WRITE_FD_IDX 1
# define STDIN_PIPE 0x1
# define STDOUT_PIPE 0x2
# define BUFFER_SIZE 255
# define FD_MAX 255
# define PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# define PARSE_ERR "PARSING ERROR"
# define SPLIT_ERR "ft_split Error"
# define INPUT_OPEN_ERR "input file open"

/* bash Error */
# define NO_SUCH_FILE "No such file or directory"
# define BAD_FD "Bad file descriptor"
# define UNEXPECTED_TOKEN "syntax error near unexpected token `&\'"

# define FILE_OPEN_ERR "file open Error"
# define OUTPUT_OPEN_ERR "redirection output file open"
# define COMMAND_NOT_EXIST "command program not exist"
# define ENV_PATH_NOT_EXIST "system env PATH not exist"
# define DUP2_ERR "dup2"
# define ENV_PATH_NOT_EXIST "system env PATH not exist"
# define PIPE_ERR "create pipe Error"
# define READ_ERR "read result [-1]"
# define UNLINK_ERR "file remove Error"
# define TEMP_FILE ".temp.txt"
# define EXPORT_FILE ".export.txt"
# define EXPORT_FILE_2 ".export_2.txt"
# define ENV_FILE ".env.txt"
# define ENV_FILE_2 ".env_2.txt"


#endif
