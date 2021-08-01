/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:05:24 by taesan            #+#    #+#             */
/*   Updated: 2021/08/01 14:29:46 by taesan           ###   ########.fr       */
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
	char	**paths;
	char	**param;
	char	**envp;
	int		command_cnt;
	int		single_q;
	int		double_q;
	int 	pipe_cnt;
	int		is_builtin;
	char 	start_q;
	t_list	*commands;
}				t_info;

typedef struct s_pipe
{
	char		**param;
	char		**envp;
	const char	*out_file;
	int			pipe_in[2];
	int			pipe_out[2];
	int			connect_pipe[2];
	int			result_fd;
}				t_pipe;

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


# define PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# define SPLIT_ERR "ft_split Error"
# define MALLOC_ERR "malloc Error"
# define WAIT_ERR "wait func return Error [-1]"
# define SUBSTR_ERR "ft_substr Error"
# define STRJOIN_ERR "ft_strjoin Error"
# define MAKE_NEW_INPUT_ERR "make new input Error"
# define FILTER_INPUT_ERR "filter_input error"
/*
	pipex defines ...ref..
*/

# define READ_FD_IDX 0
# define WRITE_FD_IDX 1
# define DUP2_ERR "dup2"
# define STDIN_PIPE 0x1
# define STDOUT_PIPE 0x2




#endif
