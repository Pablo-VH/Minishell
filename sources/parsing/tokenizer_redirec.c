/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:43:27 by dgargant          #+#    #+#             */
/*   Updated: 2025/05/06 11:11:25 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"


void	take_pipes(t_pipes *data, char *line)
{
	int i;
	
	i = data->pars->i + 1;
	data->pars->count = i;
	count_cmds(data, line);
	take_token(data);
	data->pars->np2 = 0;
	data->pars->c_cmd++;
	count_node_files(data, line, i);
}

// retocar para cosas especificas a futuro
/*esta funcion recoge los delimitadores del heredoc
y actualiza el nodo con reset_comand()*/
void	take_hdelimiter(t_pipes *data, char *line)
{
	int i;
	int j;
	char *limiter;

	i = data->pars->i + 1;
	j = 0;
	limiter = NULL;
	while (!(line[i] >= '!' && line[i] <= 126))
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
		}else if (line[j] == '<' || line[j] == '>' || line[j] == '|')
			break;
		if (!(line[j] >= '!' && line[j] <= 126))
			break;
		j++;
	}
	if (line[j] == '<' || line[j] == '>' || line[j] == '|')
		data->pars->i = j - 1;
	else	
		data->pars->i = j;
	if (line[i] == '"' || line[i] == '\'')
	{
		j--;
		i++;
		//data->pars->hrd_n = 1;
	}
	limiter = ft_substr(line, i, (j - i));
	set_node_files(data, limiter, N_HRD);
}

/* Esta funcion recoge el infile y lo inserta en el nuevo nodo
	generado del siguiente comando*/
void	take_tfile(t_pipes *data, char *line, int flagfd)
{
	int	i;
	int j;
	char *file;

	i = data->pars->i + 1;
	j = 0;
	(void)flagfd; 
	while (!(line[i] >= '!' && line[i] <= 126))
		i++;
	j =  i;
	while(line[j])
	{
		/*gestionar comillas tanto en los comandos 
			como en los ficheros (to do)*/
		//printf("-> %c", line[j] );
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
		if (!(line[j] >= '!' && line[j] <= 126))
			break;
		j++;
	}
	if (line[j] == '<' || line[j] == '>' || line[j] == '|')
		data->pars->i = j - 1;
	else	
		data->pars->i = j;
	if (line[i] == '"' || line[i] == '\'')
	{
		j--;
		i++;
	}
	file = ft_substr(line, i, (j - i));
	set_node_files(data, file, flagfd);
}
