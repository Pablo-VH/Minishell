/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_counters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:40:00 by dgargant          #+#    #+#             */
/*   Updated: 2025/03/26 12:46:56 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

// Funcion que cuenta el numero de heredocks
void	count_heredocs(t_pipes *data, char *line)
{
	int	i;
	int	hdoc;

	i = 0;
	hdoc = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] != '"')
				i++;
			i++;
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				i++;
			i++;
		}else if (line[i] == '<' && line[i + 1] == '<')
		{
			data->nhrd = ++hdoc;
			i++;
		}
		i++;
	}
}

// funcion para contar numero de pipes
void	count_pipes(t_pipes *data, char *line)
{
	int	i;
	int	npipe;

	i = 0;
	npipe = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] != '"')
				i++;
			i++;
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				i++;
			i++;
		}else if (line[i] == '|' )
		{
			data->npipes = ++npipe;
			i++;
		}
		i++;
	}
}

/* Funcion que cuenta el numero de comandos en la pipe
	para la reserva de memoria del doble puntero*/

int	ft_is_token(char *line, int i)
{
	return((line[i] == '<' || line[i] == '>')
		|| (line[i] == '<' && line[i + 1] == '<')
		|| (line[i] == '>' && line[i + 1] == '>'));
}

void	count_cmds(t_pipes *data, char *line)
{
	int	ncmds;
	int	i;

	i = data->pars->count;
	ncmds = 0;
	while (line[i])
	{
		while (line[i] && !(line[i] >= '!' && line[i] <= 126))
			i++;
		if (line[i] == '"')
		{	
			i++;
			ncmds++;
			while (line[i] != '"')
				i++;
			i++;
		} else if (line[i] == '\'')
		{
			i++;
			ncmds++;
			while (line[i] != '\'')
				i++;
			i++;
		}else if (ft_is_token(line, i))
		{
			i++;
			if (ft_is_token(line, i))
			{
				i++;
			}
			if (!ft_is_token(line, i))
			{
				while (!(line[i] >= '!' && line[i] <= 126))
					i++;
				while (line[i])
				{
					if (line[i] == '"' || line[i] == '\'')
					{
						i++;
						while (line[i] != '"' && line [i] != '\'')
						{
							i++;
						}
					}
					if ((line[i] == '<' || line[i] == '>' || line[i] == '|')
					|| !(line[i] >= '!' && line[i] <= 126))
					{
						break;
					}
					i++;
				}
				while (line[i] && !(line[i] >= '!' && line[i] <= 126))
					i++;
				if (line[i] == '|')
					break;
				if (line[i])
				{	
					if (!ft_is_token(line, i) || !(line[i] >= '!' && line[i] <= 126))
					{
						ncmds++;
						while(line[i])
						{
							if ((line[i + 1] == '<' || line[i + 1] == '>' || line[i + 1] == '|')
							|| !(line[i] >= '!' && line[i] <= 126))
								break;
							i++;
						}
					}
					if (ft_is_token(line, i))
						i--;
				}
			}
			if (!line[i])
				break;
		} else if (line[i] == '|')
			break;
		else if (line[i] && (!ft_is_token(line, i)))
		{
			ncmds++;
			while (line[i])
			{
				if ((line[i] == '<' || line[i] == '>' || line[i] == '|')
						|| !(line[i] >= '!' && line[i] <= 126))
						break;
				i++;
			}
			if (!line[i])
				break;
		}
		i++;
	}
	//write(1, "hola", 4);
	data->pars->count = i;
	data->pars->ncmds[data->pars->np] = ncmds;
	//printf("\n Num comandos en el nodo %d \n", ncmds);
	data->pars->np++;
}

/*Cuenta los ficheros de cada nodo, incluido los heredocs
	y reserba memoria para guardarlos despues*/
// hay que modificarlo para que cuente teniendo en cuenta comillas
void	count_node_files(t_pipes *data, char *line, int i)
{
	t_cmds *nd;

	nd = ft_lstlast(data->cmds);
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] != '"')
				i++;
			i++;
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				i++;
			i++;
		}else if (line[i] == '<' && line[i + 1] == '<')
		{
			nd->s_files->nfiles++;
			i+= 2;
		}	
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			nd->s_files->nfiles++;
			i+=2;
		}
		else if (line[i] == '<' || line[i] == '>')
			nd->s_files->nfiles++;
		i++;
	}
	if (nd->s_files->nfiles > 0)
	{
		nd->s_files->file = ft_calloc(nd->s_files->nfiles + 1, sizeof(char *));
		nd->s_files->flagfd = ft_calloc(nd->s_files->nfiles + 1, sizeof(int));
	}
}
