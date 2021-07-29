#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct	s_minishell
{
	pid_t	sib_pid;
	int		sib_p_state;
	char	*read_line;
	char	**parsing_line;
	char	**envp;
	t_list	*cmdlst;
	t_list	*cmdlst_head;
}				t_minishell;

t_list			*cmdlst_new(void);
void			cmdlst_add(t_list *lst, void *content);
void			free_cmdlst(t_list *lst);
void			minishell_roop(t_minishell *ms);
void			start_sibling_process(t_minishell *ms);
int				get_str_len(t_minishell *ms, char *line);
char			*put_str(t_minishell *ms, char *line, char *str);

#endif
