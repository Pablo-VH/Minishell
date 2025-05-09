/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:07:08 by dgargant          #+#    #+#             */
/*   Updated: 2025/05/06 11:11:07 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

// retocar para cosas especificas
// Esta funcion crea un (char *) con el comando
// hay que recoger el comando teniendo en cuenta comillas
// no hay que recoger las comillas
char	*take_cmd(t_pipes *data,char *line ,int i)
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
		}
		else if (line[j] == '\'')
		{
			j++;
			while (line[j] != '\'')
				j++;
		}else if ((line[j] == '<' || line[j] == '>' || line[j] == '|'))
			break;
		if  (!(line[j] >= '!' && line[j] <= 126))
			break;
		j++;
	}
	data->pars->i = j;
	if (i != j)
		cmd = ft_substr(line, i, (j - i));
	else
		cmd = NULL;
	
	return (cmd);
}


void	insert_cmds(t_pipes *data, char *comand)
{
	t_cmds *last;

	last = NULL;
	if (data->cmds)
	{
		last = ft_lstlast(data->cmds);
		if (!last->cmds)
		{
			last->cmds = ft_calloc(data->pars->ncmds[data->pars->c_cmd] + 1, sizeof(char *));
			last->cmds[data->pars->np2] = comand;
			data->pars->np2++;
		}
		else
		{
			last->cmds[data->pars->np2] = comand;
			data->pars->np2++;
		}
	}
}

// recoge el primer comando
// hay que recoger el comando teniendo en cuenta comillas
// no hay que recoger las comillas
void take_fist_token(t_pipes *data ,char *line)
{
	//int i;
	//int j;
	//char *comand;
	
	//i = 0;
	//comand = NULL;
	count_cmds(data, line);
	// es posible que pueda cambiar esta parte por take_cmd()
	/*while (line[i] && !(line[i] >= '!' && line[i] <= 126))
		i++;
	j = i;
	while(line[j])
	{
		if (line[j] == '"')
		{
			j++;
			while (line[j] != '"')
				j++;
		}
		else if (line[j] == '\'')
		{
			j++;
			while (line[j] != '\'')
				j++;
		}else if (line[j] == '<' || line[j] == '>' || line[j] == '|')
			break;
		if  (!(line[j] >= '!' && line[j] <= 126))
			break;
		j++;
	}
	comand = ft_substr(line, i, (j - i));*/
	//printf("\n<<< %s >>>\n", comand);
	take_token(data);
	//insert_cmds(data, comand);
	count_node_files(data, line, data->pars->i);
	/*if ((comand[0] == '\0'))
		return (j);
	return(j);*/
}


// esta funcion genera cada nodo de la lista
void	take_token(t_pipes *data)
{
	t_cmds *cmd;
	
	cmd = NULL;
	if (!data->cmds)
			data->cmds = ft_lstnew();
	else
	{
		cmd = ft_lstnew();
		ft_lstadd_back(data->cmds, cmd);
	}
	data->num_cmds++;
	data->pars->np2 = 0;
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

