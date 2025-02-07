/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:43:27 by dgargant          #+#    #+#             */
/*   Updated: 2025/02/07 10:47:23 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"


void	take_pipes(t_pipes *data, char *line, int i)
{
	char *comand;
	
	comand = NULL;
	comand = take_cmd(line, i);
	take_token(data, comand);
	count_node_files(data, line, i);
}

// retocar para cosas especificas a futuro
/*esta funcion recoge los delimitadores del heredoc
y actualiza el nodo con reset_comand()*/
void	take_hdelimiter(t_pipes *data, char *line, int i)
{
	int j;
	char *comand;
	char *limiter;

	j = 0;
	comand = NULL;
	limiter = NULL;
	while (!(line[i] >= '!' && line[i] <= 126))
		i++;
	j =  i;
	while(line[j])
	{
		j++;
		if (!(line[j] >= '!' && line[j] <= 126) 
		|| (line[j] == '<' || line[j] == '>' || line[j] == '|'))
			break;
	}
	limiter = ft_substr(line, i, (j - i));
	set_node_files(data, limiter, N_HRD);
	/*data->limiters[ndoc] = ft_substr(line, i, (j - i));
	if (!data->limiters[ndoc])
		ft_free_array(data->limiters);*/
	if (!(line[j] == '<' || line[j] == '>' || line[j] == '|'))
	{
		comand = take_cmd(line, j);
		reset_comand(data, comand);
	}
	//(void)cmd;
	//printf("%d -> %s\n", ndoc ,data->limiters[ndoc]);
	//printf(" > %s\n", comand);
	//printf(" > %s\n", data->cmds->cmd);
}

/* Esta funcion recoge el infile y lo inserta en el nuevo nodo
	generado del siguiente comando*/
void	take_tfile(t_pipes *data, char *line, int flagfd, int i)
{
	int j;
	char *comand;
	char *file;

	j = 0;
	comand = NULL;
	(void)flagfd; 
	while (!(line[i] >= '!' && line[i] <= 126))
		i++;
	j =  i;
	while(line[j])
	{
		j++;
		if (!(line[j] >= '!' && line[j] <= 126) 
		|| (line[j] == '<' || line[j] == '>' || line[j] == '|'))
			break;
	}
	file = ft_substr(line, i, (j - i));
	if (!( line[j] == '|'))
	{
		comand = take_cmd(line, j);
		reset_comand(data, comand);
		set_node_files(data, file, flagfd);
	}
	//(void)cmd;
	//printf("%d -> %s\n", ndoc ,data->limiters[ndoc]);
	//printf(" > %s\n", comand);
	//printf(" > %s\n", data->cmds->cmd);
}