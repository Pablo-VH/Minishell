/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:42:09 by pavicent          #+#    #+#             */
/*   Updated: 2024/10/15 13:42:11 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include "libft.h"
# include "ft_printf.h"
# include <sys/wait.h>
# define BUFFER_LENGTH 1024

typedef struct s_docs
{
	int		flag;
	char	*file;
	char	*cmd;
	int		fd;
}			t_docs;

typedef struct s_lists
{
	t_docs			*docs;
	struct s_lists	*next;
}					t_lists;

typedef struct s_pipes
{
	int		**fd;
	char	*limiter;
	int		mode;
	pid_t	*pids;
	int		num_cmds;
	t_lists	*list;
}			t_pipes;

char	*ft_getenv(char *name, char **env);
char	*get_path(char	*cmd, char **env);
int		add_list(t_lists *list);
int		child_process(t_pipes *data, char **env, int i, t_lists *tmp);
int		do_fork(t_pipes *data, int i);
int		get_cmd(t_pipes *data, char **av, int i);
int		init_fd(t_pipes *data);
int		init_list(t_pipes *data);
int		init_pid(t_pipes **data);
void	check_args(t_pipes *data, char **av, int ac);
void	check_fd_in(int *fd);
void	check_fd_out(t_pipes *data);
void	close_files(t_lists *list);
void	close_pipes(t_pipes *data, int i);
void	do_pipe2(char *cmd, char **env, int fd, int *p_fd);
void	exec(char *cmd, char **env, t_pipes *data, t_lists *tmp);
void	exit_handler(int n_ex);
void	free_fd(t_pipes *data);
void	free_lists(t_lists *lst);
void	ft_free_struct(t_pipes *data);
void	ft_free_tab(char **tab);
void	here_doc(t_pipes *data);
void	here_doc_put_in(t_pipes *data, int i);
void	init_files(t_pipes *data);
void	init_inflag(t_pipes *data);
void	init_outflags(t_lists *lst, t_lists *first);
void	open_file(char *file, int in_or_out, int *fd);
void	parent_process(t_pipes *data, int i, char **env);
void	pipes_redirs(t_pipes *data, int i, t_lists *list);
void	redir_files(t_pipes *data, t_lists *list);
void	wait_pids(t_pipes *data, int i);

#endif
