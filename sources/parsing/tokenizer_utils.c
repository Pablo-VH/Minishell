/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:07:08 by dgargant          #+#    #+#             */
/*   Updated: 2025/03/28 12:36:42 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

// retocar para cosas especificas
// Esta funcion crea un (char *) con el comando
// hay que recoger el comando teniendo en cuenta comillas
// no hay que recoger las comillas
char	*take_cmd(char *line ,int i)
{
	int 	j;
	char	*cmd;
	while (line[i] && !(line[i] >= '!' && line[i] <= 126))
		i++;
	j =  i;
	while(line[j])
	{
		if (line[j] == '"')
		{
			j++;
			while (line[j] != '"')
				j++;
			j++;
		}
		else if (line[j] == '\'')
		{
			j++;
			while (line[j] != '\'')
				j++;
			j++;
		}else if ((line[j] == '<' || line[j] == '>' || line[j] == '|'))
			break;
		if  (!(line[j] >= '!' && line[j] <= 126))
			break;
		j++;
	}
	cmd = ft_substr(line, i, (j - i));
	return (cmd);
}


// recoge el primer comando
// hay que recoger el comando teniendo en cuenta comillas
// no hay que recoger las comillas
int take_fist_token(t_pipes *data ,char *line)
{
	int i;
	int j;
	char *comand;
	
	i = 0;
	comand = NULL;
	count_cmds(data, line);
	// es posible que pueda cambiar esta parte por take_cmd()
	while (line[i] && !(line[i] >= '!' && line[i] <= 126))
		i++;
	j = i;
	while(line[j])
	{
		if (line[j] == '"')
		{
			j++;
			while (line[j] != '"')
				j++;
			j++;
		}
		else if (line[j] == '\'')
		{
			j++;
			while (line[j] != '\'')
				j++;
			j++;
		}else if (line[j] == '<' || line[j] == '>' || line[j] == '|')
			break;
		if  (!(line[j] >= '!' && line[j] <= 126))
			break;
		j++;
	}
	comand = ft_substr(line, i, (j - i));
	//printf("\n<<< %s >>>\n", comand);
	take_token(data, comand);
	count_node_files(data, line, i);
	if ((comand[0] == '\0'))
		return (j);
	return(j);
}

// esta funcion genera cada nodo de la lista
void	take_token(t_pipes *data, char *comand)
{
	t_cmds *cmd;
	
	cmd = NULL;
	if (!data->cmds)
			data->cmds = ft_lstnew(comand);
	else
	{
		cmd = ft_lstnew(comand);
		ft_lstadd_back(data->cmds, cmd);
	}
	data->num_cmds++;
}


/* Esta funcion actualiza el contenido del nodo cmd
y lo crea si este no esta inicializado */
void	reset_comand(t_pipes *data,char *comand)
{
	t_cmds *last;
	char *tmp;
	
	last = NULL;
	tmp = NULL;

	if (data->cmds)
	{
		//write(1, "hello", 5);
		last = ft_lstlast(data->cmds);
		tmp = last->cmd;
		/*join con espacio*/
		last->cmd = ft_superjoin(tmp, ' ' ,comand);
		free(tmp);
		free(comand);
	} else
		data->cmds = ft_lstnew(comand);
}


/*Funcion que introduce los ficheros y el tipo de redireccion
	en los punteros de la structura files*/
void	set_node_files(t_pipes *data, char *file, int flagfd)
{
	int i;
	t_cmds *current;
	
	i = 0;
	current = ft_lstlast(data->cmds);
	while (i < current->s_files->nfiles)
	{
		if (!current->s_files->file[i] 
			&& !current->s_files->flagfd[i])
		{
			current->s_files->file[i] = file;
			current->s_files->flagfd[i] = flagfd;
			return;
		}
		else
			i++;
	}
}

