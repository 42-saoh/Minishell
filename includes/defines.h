/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:05:24 by taesan            #+#    #+#             */
/*   Updated: 2021/08/14 00:21:03 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

#include "minishell.h"

/*
	명령어에서 아래 문자들이 존재하는지 ..
	single, double모두 존재할 경우, 1번이 먼저 나옴.
*/
typedef struct s_info
{
	char	**paths; // 계속 씀.
	char	**param; // parents에서 free됨.
	char	**envp; // 계속 씀.
	int		command_cnt; // 초기화
	int		is_builtin; // 초기화
	t_list	*commands; // lstclear함.
	t_list	*redirect_lst;
	t_list	*commands_symbol;
	int			pipe_in[2];
	int			pipe_out[2];
	int			connect_pipe[2];
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
# define BUFFER_SIZE 256
# define FD_MAX 255
# define PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# define PARSE_ERR "PARSING ERROR"
# define SPLIT_ERR "ft_split Error"
# define INPUT_OPEN_ERR "input file open"
# define NO_SUCH_FILE "No such file or directory"
# define OUTPUT_OPEN_ERR "redirection output file open"
# define COMMAND_NOT_EXIST "command program not exist"
# define ENV_PATH_NOT_EXIST "system env PATH not exist"
# define DUP2_ERR "dup2"
# define ENV_PATH_NOT_EXIST "system env PATH not exist"
# define PIPE_ERR "create pipe Error"
# define READ_ERR "read result [-1]"
# define UNLINK_ERR "file remove Error"
# define HERE_DOC "here_doc"
# define TEMP_FILE ".temp.txt"




#endif
