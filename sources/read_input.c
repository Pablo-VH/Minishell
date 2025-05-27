/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:45:30 by pavicent          #+#    #+#             */
/*   Updated: 2025/05/19 13:45:32 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

void	read_input(t_pipes *data)
{
	char	*line;

	line = NULL;
	while (1)
	{
		signal(SIGINT, handler);
		line = readline(PURPLE"Gertru$ "RESET);
		if (line == NULL)
			ft_exit(data, 0, NULL);
		if (line != NULL)
		{
			data->pars = ft_calloc(1, sizeof(t_pars));
			parsing_init(data, line);
			free(data->pars);
			data->pars = NULL;
			if (line[0] != '\0')
				execute(data);
			delete_hd(data);
			ft_free_struct2(data);
		}
		add_history(line);
		free(line);
	}
}
