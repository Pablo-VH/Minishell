/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gertru.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:51:48 by dgargant          #+#    #+#             */
/*   Updated: 2025/05/18 23:11:43 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GERTRU_H
# define GERTRU_H


# include "libft.h"

// for printf, readline, perror
# include <stdio.h>
// for strerror
# include <string.h>
// for malloc, free, exit, getenv
# include <stdlib.h>
// for write, access, close, read, getcwd, chdir,
// unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot
# include <unistd.h>
// stat, lstat, fstat
# include <sys/stat.h>
// for read, wait3, wait4
# include <sys/types.h>
// for read
# include <sys/uio.h>
// for open
# include <fcntl.h>
// for signal, sigaction, kill
# include <signal.h>
// for fork, kill
# include <sys/types.h>
// for waitpid, wait, waitpid, wait3, wait4
# include <sys/wait.h>
// for wait3, wait4
# include <sys/time.h>
// for wait3, wait4
# include <sys/resource.h>
// for readline, rl_on_new_line, rl_redisplay, add_history
# include <readline/readline.h> /* rl_clear_history, rl_redisplay ? */
// for readline, rl_on_new_line, rl_redisplay, add_history
# include <readline/history.h> /* rl_clear_history, rl_redisplay ? */
// for opendir, readdir, closedir
# include <dirent.h>
// for ioctl
# include <sys/ioctl.h>
// for tcsetattr, tcgetattr
# include <termios.h>
// for tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <curses.h>
// for tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <term.h>
// for errno
# include <errno.h>
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[0;32m\002"
# define PURPLE "\001\033[0;95m\002"
# define RESET "\001\033[0m\002"
# define N_NF -1 // no tiene fichero
# define N_INF 0 // es infile
# define N_OUTF 1 // es outfile
# define N_HRD 2 // es heredoc
# define N_AOUTF 3 // es outfile en modo apend

extern unsigned char	g_exit_status;

typedef struct s_files
{
	char	**file; // doble puntero con los fichero del nodo (done)
	int		*flagfd; // tipo de redireccion/ejecuciones (done)
	int		*fd; // fd del documento (pav)
	int		nfiles; // numero de ficheros en el nodo  (done)
}			t_files;

typedef struct s_cmds
{
	char			**cmds; // doble puntero de los comandos
	t_files			*s_files; // estructura ficheros del nodo (done)
	int				stop_exec;
	struct s_cmds	*next;
}			t_cmds;

typedef struct s_pars
{
	char	c;
	int		fdb; //flag comillas dobles
	int		fs; //flag comillas simples
	int		count; //contador
	int		np;
	int		np2;
	int		count_f;
	int		i; // contador de posicion en la tiena de tokenizado
	int		c_cmd; // contador del puntero de ncmds
	int		*ncmds; //puntero con el numero de comandos de cada nodo
	int		*nfiles;
}			t_pars;

typedef struct s_pipes
{
	int		**fd; // fds de los pipes
	int		mode; // (pav)
	pid_t	*pids; // (forks)
	int		num_cmds; // num comandos (to do)
	char	**env; // puntero a enviroment (done)
	int		nhrd; // numero de heredocs (done)
	int		npipes; // numero de pipes (to do)
	char	*pwd;
	char	*oldpwd;
	int		stop_exec_hd;
	int		status;
	t_cmds	*cmds; // lista de comandos
	t_pars	*pars; // estructura de datos de parseo
}			t_pipes;

typedef enum s_aut
{
	A_INI,
	A_ERR,
	A_SPA,
	A_PRI,
	A_DOB,
	A_SIN,
	A_PIP,
	A_RIN,
	A_ROU,
	A_RIO,
}	t_aut;

typedef enum s_tok
{
	T_INI,
	T_ERR,
	T_SPA,
	T_PRI,
	T_DOB,
	T_SIN,
	T_PIP,
	T_RIN,
	T_ROU,
	T_COM,
}	t_tok;

void	handler(int signal);

char	*expand_init(t_pipes *data, char *line);

char	*insert_expansion(char *line, char * var, char *exp, int i);

char	*search_in_env(t_pipes *data, char *v_search);

char	*take_cmd(t_pipes *data,char *line ,int i);

char	*take_v(char *line, int i);

int		check_state(int prev, char c);

int		ft_check_syntax(char *line);

int		ft_is_token(char *line, int i);

int		get_state(int prev, int pos);

int		syntax_init(char *line);

void	count_cmds(t_pipes *data, char *line);

void	count_heredocs(t_pipes *data, char *line);

void	count_node_files(t_pipes *data, char *line, int i);

void	count_pipes(t_pipes *data, char *line);

void	delete_some_quotes(t_pipes *data, char *line, char *new_line, int i);

void	insert_cmds(t_pipes *data, char *comand);

void	parsing_init(t_pipes *data, char *line);

void	read_input(t_pipes *data);

void	set_node_files(t_pipes *data, char *file, int flagfd);

void	take_first_token(t_pipes *data, char *line);

void	take_hdelimiter(t_pipes *data, char *line);

void	take_pipes(t_pipes *data, char *line);

void	take_quote(t_pipes *data, char *line, char c, int mode);

void	take_tfile(t_pipes *data, char *line, int flagfd);

void	take_token(t_pipes *data);

void	tokenizer_init(t_pipes *data, char *line);

void	token_count_files(t_pipes *data, char *line);

void	token_count_cmds(t_pipes *data, char *line);

char	*take_quote2(t_pipes *data, char *line, char *cmd, int j);

//Utils

char	**ft_init_env(char **str);

int		ft_array_length(char **str);

int		ft_lgth(const char *s1, const char *s2);

int		init_pid(t_pipes **data);

int		init_fd(t_pipes *data);

t_cmds	*ft_lstlast(t_cmds *lst);

void	ft_lstadd_back(t_cmds *slst, t_cmds *new);



// list utils files

/*t_files	*file_lstlast(t_files *lst);

void	file_lstadd_back(t_files *lst, t_files *new);

t_files	*file_lstnew(int flagfd);*/

//t_cmds	*ft_lstnew(int flagfd, char *cmd, char *file);

t_cmds	*ft_lstnew(void);

//Frees

void	free_fd(t_pipes *data);

void	ft_free_struct(t_pipes *data);

void	ft_free_tab(char **str);

void	close_files(t_cmds *list);

void	close_pipes(t_pipes *data, int i);

void	redir_files(t_pipes *data, t_cmds *list);

void	ft_free_all(t_pipes *data);

void	reset_int(t_pipes *data);

void	ft_free_s_files(t_files *files);

void	ft_free_pids(pid_t **pids);

void	ft_free_lst(t_pipes *data);

void	ft_free_struct2(t_pipes *data);

//execs
char	*ft_find_env_var(char *envp[], char *var, int len);

int		check_builtin(t_pipes *data, int in_child);

void	execute(t_pipes *data);

void	ft_echo(t_pipes *data, char **builtin);

void	ft_cd(t_pipes *data, char **builtin);

void	write_error(char *msg, char *arg);

void	write_n_change_status(char *msg, int status);

void	ft_cd(t_pipes *data, char **builtin);

void	unset(t_pipes *data);

void	export(t_pipes *data);

void	print_env(t_pipes *data);

void	pipes_redirs(t_pipes *data, int i, t_cmds *list);

void	get_pwd(t_pipes *data);

void	wait_pids(t_pipes *data, int i);

int		ft_exit(t_pipes *data, int in_child, char **builtin);


//files
int		heredoc(t_pipes *data, int i);

void	open_tmp_file(t_pipes *data, int i);

int		append(t_pipes *data, int i);

int		outfile(t_pipes *data, int i);

int		outfile(t_pipes *data, int i);

int		infile(t_pipes *data, int i);

void	cmds_exec(t_pipes *data);

void	executor(t_pipes *data, t_cmds *tmp);

void	delete_hd(t_pipes *data);

#endif