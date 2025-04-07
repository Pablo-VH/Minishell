/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gertru.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:51:48 by dgargant          #+#    #+#             */
/*   Updated: 2025/02/07 09:48:46 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GERTRU_H
# define GERTRU_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
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
	int		*exp;
}			t_files;

typedef struct s_cmds
{
	char			*cmd; // puntero del comando (done)
	t_files			*s_files; // estructura ficheros del nodo (done)
	char			**args;
	int				stop_exec;
	struct s_cmds	*next;
}			t_cmds;

typedef struct s_pars
{
	int		fdb; //flag comillas dobles
	int		fs; //flag comillas simples
	int		count; //contador
	int		np;
	int		*ncmds;
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
	//int		nfiles; // numero de archivos
	int		flag;
	t_cmds	*cmds; // lista de comandos
	t_pars *pars; // estructura de datos de parseo
}			t_pipes;


void	read_imput(t_pipes *data);

void	parsing_init(t_pipes *data, char *line);

void	tokenizer_init(t_pipes *data, char *line);

int		init_fd(t_pipes *data);

int		init_pid(t_pipes **data);

void	take_hdelimiter(t_pipes *data, char *line, int i);

void	take_tfile(t_pipes *data, char *line, int flagfd, int i);

void	count_heredocs(t_pipes *data, char *line);

void	count_pipes(t_pipes *data, char *line);

void	count_node_files(t_pipes *data, char *line, int i);

char	*take_cmd(char *line, int i);

void	take_token(t_pipes *data, char *comand);

int		take_fist_token(t_pipes *data, char *line);

void	take_pipes(t_pipes *data, char *line, int i);

void	set_node_files(t_pipes *data, char *file, int flagfd);

void	reset_comand(t_pipes *data, char *comand);

int		sintax_init(t_pipes *data, char *line);

void	reset_quotes(t_pipes *data);

void	count_cmds(t_pipes *data, char *line);

int		ft_is_token(char *line, int i);

//int	is_piped(char *line, int i);

//List Utils

int		ft_array_length(char **str);

int		init_pid(t_pipes **data);

int		init_fd(t_pipes *data);

t_cmds	*ft_lstlast(t_cmds *lst);

void	ft_lstadd_back(t_cmds *slst, t_cmds *new);

// list utils files

/*t_files	*file_lstlast(t_files *lst);

void	file_lstadd_back(t_files *lst, t_files *new);

t_files	*file_lstnew(int flagfd);*/

//t_cmds	*ft_lstnew(int flagfd, char *cmd, char *file);

t_cmds	*ft_lstnew(char *cmd);

//Frees

void	free_fd(t_pipes *data);

void	ft_free_struct(t_pipes *data);

void	ft_free_tab(char **tab);

void	free_lists(t_cmds *lst);

void	close_files(t_cmds *list);

void	close_pipes(t_pipes *data, int i);

void	redir_files(t_pipes *data, t_cmds *list);

void	ft_free_all(t_pipes *data);

//execs
int		check_builtin(t_pipes *data, int in_child);

void	execute(t_pipes *data);

void	ft_echo(t_pipes *data, char **builtin);

void	ft_cd(t_pipes *data, char **builtin);

void	write_error(char *msg, char *arg);

int		ft_exit(t_pipes *data, int in_child, char **builtin);

void	ft_cd(t_pipes *data, char **builtin);

void	unset(t_pipes *data);

void	export(t_pipes *data);

void	print_env(t_pipes *data);

void	pipes_redirs(t_pipes *data, int i, t_cmds *list);

//files
int		heredoc(t_pipes *data, int i);

void	open_tmp_file(t_pipes *data, int i);

int		append(t_pipes *data, int i);

int		outfile(t_pipes *data, int i);

int		outfile(t_pipes *data, int i);

int		infile(t_pipes *data, int i);

void	cmds_exec(t_pipes *data);

void	executor(t_pipes *data, t_cmds *tmp);

#endif