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
# include "../libft/libft.h"
# include <fcntl.h>

# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[0;32m\002"
# define PURPLE "\001\033[0;95m\002"
# define RESET "\001\033[0m\002"


# define N_NF -1 // no tiene fichero
# define N_INF 0 // es infile
# define N_OUTF 1 // es outfile
# define N_HRD 2 // es heredoc
# define N_AOUTF 3 // es outfile en modo apend

typedef struct s_files
{
	char			**file; // doble puntero con los fichero del nodo (done)
	int				*flagfd; // numero que indica que tipo de redireccion/ejecuciones (done)
	int				*fd; // fd del documento (pav)
	int				nfiles; // numero de ficheros en el nodo  (done)
}		t_files;

typedef struct s_cmds
{
	char			*cmd; // puntero del comando (done)
	t_files			*s_files; // estructura que contiene los ficheros del nodo (done)
	struct s_cmds	*next;
}			t_cmds;

/*typedef struct s_parse
{
	int		nfiles;
}			t_parse;*/


typedef struct s_pipes
{
	int		**fd; // fds de los pipes
	//char	**limiters; // palabras delimitadoras de los heredoc (done)  <<== pasar a s_files
	//char	**files; // contiene todos los archivos
	int		mode; // (pav)
	pid_t	*pids; // (forcks)
	int		num_cmds; // num comandos (to do)
	char	**envps; // puntero a enviroment (done)
	int		nhrd; // numero de heredocs (done)
	int		npipes; // numero de pipes (to do)
	//int		nfiles; // numero de archivos
	int		flag;
	t_cmds	*cmds; // lista de comandos
	//t_parse *parse; // estructura de datos de parseo
}			t_pipes;


int		main(int argc, char **argv, char **envp);

void	read_imput(t_pipes *data);

void	parsing_init(t_pipes *data, char *line);

void	tokenizer_init(t_pipes *data, char *line);

int		init_fd(t_pipes *data);

int		init_pid(t_pipes **data);

void	take_hdelimiter(t_pipes *data, char *line, int i);

void	take_tfile(t_pipes *data, char *line, int flagfd, int i);

void	count_heredocs(t_pipes *data,char *line);

void	count_pipes(t_pipes *data, char *line);

void	count_node_files(t_pipes *data, char *line, int i);

char	*take_cmd(char *line ,int i);

void	take_token(t_pipes *data, char *comand);

int		take_fist_token(t_pipes *data ,char *line);

void	take_pipes(t_pipes *data, char *line, int i);

void	set_node_files(t_pipes *data, char *file, int flagfd);

void	reset_comand(t_pipes *data,char *comand);

//int	is_piped(char *line, int i);

//List Utils

int		init_pid(t_pipes **data);

int		init_fd(t_pipes *data);

t_cmds	*ft_lstlast(t_cmds *lst);

void	ft_lstadd_back(t_cmds *slst, t_cmds *new);

// list utils files

t_files	*file_lstlast(t_files *lst);

void	file_lstadd_back(t_files *lst, t_files *new);

t_files	*file_lstnew(int flagfd);

//t_cmds	*ft_lstnew(int flagfd, char *cmd, char *file);

t_cmds	*ft_lstnew(char *cmd);

//Frees

void	free_fd(t_pipes *data);

void	ft_free_struct(t_pipes *data);

void	ft_free_tab(char **tab);

void	free_lists(t_cmds *lst);

void	close_files(t_cmds *list);

#endif