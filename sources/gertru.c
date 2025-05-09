/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gertru.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:34:28 by dgargant          #+#    #+#             */
/*   Updated: 2025/05/08 13:23:08 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

/* Funcion que recive la linea de readline()
y llama al resto de funciones principales*/
unsigned char	g_exit_status = 0;

void	read_imput(t_pipes *data)
{
	char *line = NULL;
	//int i = 0;
	
	while (1)
	{
		line = readline(PURPLE"Gertru$ "RESET);
		if (line == NULL)
			break;
		if (line != NULL)
		{
			data->pars = ft_calloc(1, sizeof(t_pars));
			parsing_init(data, line);
			free(data->pars);
			data->pars = NULL;
			execute(data);
			//printf(" > %s" ,data->env[i]);
			//printf(" > %s\n", line);
			//i++;
			//ft_free_all(data);
			delete_hd(data);
			ft_free_struct(data);
		}
		add_history(line);
		free(line);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_pipes *data;

	(void)argv;
	data = ft_calloc(1, sizeof(t_pipes));
	data->env = ft_init_env(envp);
	if (argc == 1)
		read_imput(data);
	data->nhrd = 0;
	data->npipes = 0;
	return (0);
}

