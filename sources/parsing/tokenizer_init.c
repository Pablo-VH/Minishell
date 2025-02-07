/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:13:37 by dgargant          #+#    #+#             */
/*   Updated: 2025/02/07 10:49:55 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"


void	tokenizer_init(t_pipes *data, char *line)
{
	int i;
	
	i = take_fist_token(data, line);
	/* Esto sera una funcion que recorrera la linea
	y la tokenizara llamando a otras funciones*/
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			i++;
			take_hdelimiter(data, line,(i + 1));
		} else if (line[i] == '$')
		{
			//printf("\ndolars : %d", dolar);
		} else if (line[i] == '>' && line[i + 1] == '>')
		{
			i++;
			take_tfile(data, line, N_AOUTF, i + 1);
		}else if (line[i] == '<')
			take_tfile(data, line, N_INF, i + 1);
		else if (line[i] == '>')
			take_tfile(data, line, N_OUTF, i + 1);
		else if (line[i] == '|')
			take_pipes(data, line, i + 1);	
		i++;
	}
}

