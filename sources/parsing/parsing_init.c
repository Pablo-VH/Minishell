/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:17:38 by dgargant          #+#    #+#             */
/*   Updated: 2025/02/07 10:40:30 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"


/* Esta funcion inicializa el parseo
y llamara al resto de funciones de parseo.
Pendiente reestructuracion y cambios*/
void	parsing_init(t_pipes *data, char *rline)
{
	char *line;
	
	line = ft_strdup(rline);
	/* Aqui busco si existe algun heredoc
	para empezar a contarlos y asi
	poder reservar memoria para su doble puntero*/
	if (ft_strnstr(line, "<<", ft_strlen(line)))
		count_heredocs(data, line);
	if (ft_strnstr(line, "|", ft_strlen(line)))
		count_pipes(data, line);
		
	/* Esta funcion inicializa el tokenizado*/
	tokenizer_init(data, line);


	
	printf("Numero de pipes: %d\n", data->npipes);
	printf("Numero de Nodos: %d\n", data->num_cmds);
	printf("Numero de heredocs: %d\n", data->nhrd);
	// visualizacion de los nodos
	int i;
	i = 0;
	printf("\n<<< Nodos >>>\n \n");
	while(data->cmds)
	{
		printf("Comando --> %s\n",
			data->cmds->cmd);
		printf("Numero de ficheros: %d\n",
			data->cmds->s_files->nfiles);
		//printf("fichero %d: %s\n tipo: %d\n", i, 
		//	data->cmds->struct_files->file[i],
		//	data->cmds->struct_files->flagfd[i]);
		if (data->cmds->s_files->file)
		{
			while(data->cmds->s_files->file[i])
			{
				printf("fichero %d: %s\n tipo: %d\n", i, 
					data->cmds->s_files->file[i],
					data->cmds->s_files->flagfd[i]);
				i++;
			}
		}
		/*if (data->cmds->s_files->file == NULL)
			write(1, "hola\n",5);*/
		data->cmds = data->cmds->next;
		i = 0;
	}
	/*int j = 0;
	while (data->limiters[j])
	{
		printf(">>> %s\n", data->limiters[j]);
		j++;
	}
	printf(">>> %d\n", data->nhrd);
	printf(">>> %d\n", data->npipes);*/
	
	free(line);
}
