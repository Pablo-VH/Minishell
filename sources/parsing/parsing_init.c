/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:17:38 by dgargant          #+#    #+#             */
/*   Updated: 2025/03/28 10:33:22 by dgargant         ###   ########.fr       */
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

	/*Aqui debera ir las funciones que inicie el control
	de sintaxis y de expansion*/
	if (sintax_init(data, line))
	{
		data->pars->fdb = 0;
		data->pars->fs = 0;
		return;
	}
	/* Aqui busco si existe algun heredoc
	para empezar a contarlos y asi
	poder reservar memoria para su doble puntero*/
	if (ft_strnstr(line, "<<", ft_strlen(line)))
		count_heredocs(data, line);
	if (ft_strnstr(line, "|", ft_strlen(line)))
		count_pipes(data, line);
	// Recordar que no tiene terminacion, por lo tanto debes recorrer el puntero con npipes
	data->pars->ncmds = ft_calloc(data->npipes + 1, sizeof(int));
	//printf("Numero de heredocs: %d", data->nhrd);
	//printf("Numero de pipes: %d", data->npipes);
	//data->pars->ncmds = ft_calloc((data->npipes + 2), sizeof(int));	
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
		//	data->cmds->s_files->file[i],
		//	data->cmds->s_files->flagfd[i]);
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
		if (data->cmds->s_files->file == NULL)
			write(1, "hola\n",5);
		data->cmds = data->cmds->next;
		i = 0;
	}

	int j;
	
	j = 0;
	while (j <= (data->npipes + 1))
	{
		printf("\nNum comandos: %d\n",data->pars->ncmds[j]);
		j++;
	}
	printf("\n %d \n", data->pars->np);

	free(data->pars->ncmds);
	data->pars->ncmds  = NULL;
	data->pars->np = 0;
	data->pars->count = 0;
	data->nhrd = 0;
	data->npipes = 0;
	free(data->pars->ncmds);
	free(line);
}
