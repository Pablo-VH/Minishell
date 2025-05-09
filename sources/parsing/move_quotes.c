/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:35:06 by dgargant          #+#    #+#             */
/*   Updated: 2025/05/05 12:13:00 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

// hacemos una nueva linea del mismo tamaño con calloc
// en la vieja miro comillas caracter por caracter

void	quote_manager(t_pipes *data, char *line)
{
	int		i;
	char	*new_line;
	
	i = 0;
	new_line = ft_calloc(ft_strlen(line), sizeof(char));
	
	while (line[i])
	{
		if ((line[i] == '"' && data->pars->fdb == 0) && data->pars->fs != 1)
			data->pars->fdb = 1;
		else if ((line [i] == '"' && data->pars->fdb == 1)
			&& data->pars->fs != 1)
			data->pars->fdb = 0;
		if ((line[i] == '\'' && data->pars->fs == 0) && data->pars->fdb != 1)
			data->pars->fs = 1;
		else if ((line [i] == '\'' && data->pars->fs == 1)
			&& data->pars->fdb != 1)
			data->pars->fs = 0;
		//delete_some_quotes(data, line, new_line, i);
		i++;
	}
	printf("\n>>>>>>linea moviendo comillas: %s\n", new_line);
}

void	delete_some_quotes(t_pipes *data, char *line, char *new_line , int i)
{
	
	static int		j;

	
	j = 0;
	if ((line[i] == '"' && data->pars->fs == 1)
		|| (data->pars->fdb == 1 && line[i] == '\''))
	{
		new_line[j] = line[i];
		j++;
		printf("1 [%c], ", line[i]);
	}
	else if ((line[i] == '"' || line[i] == '\'' ) 
		&& (line[i + 1] == '"' || line[i + 1] == '\''))
	{
		printf("2 [%c], ", line[i]);
	}
	else if ((line[i] == '"' || line[i] == '\'' ) 
		&& (line[i - 1] == '"' || line[i - 1] == '\''))
	{
		printf("3 [%c], ", line[i]);
	}
	else if (ft_isprint(line[i]))
	{
		new_line[j] = line[i];
		j++;
		printf("4 [%c], ", line[i]);
	}
	
		/*if (line[i] == '"' && !ft_is_token(line, i + 1) && line[i + 1] != '|'
		&& (line[i + 1] >= '!' && line[i + 1] <= 126))
			i++;
		else
		{
			new_line[j] = line[i];
		}*/
	//printf("\n>>>>>>linea moviendo comillas: %s\n", new_line);
		
}

/*void	*move_quote_forward(t_pipes *data, char *line, char *new_line, int i)
{
	static int j;

	j = 0;
	if (line[i])
}*/

/*void	*move_quote_backward(t_pipes *data, char *line, int i)
{
	char	*new_line;

	new_line = NULL;
	
	return (new_line);
}*/


/*void	check_quotes_to_move(t_pipes *data, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == '"' && data->pars->fdb == 0) && data->pars->fs != 1)
			data->pars->fdb = 1;
		else if ((line[i] == '"' && data->pars->fdb == 1)
			&& (line[i + 1] >= '!' && line[i + 1] <= 126)
			&& data->pars->fs != 1)
			line = move_quote_forward(data, line, i);
		else if ((line[i] == '"' && data->pars->fdb == 1)
			&& (line[i - 1] >= '!' && line[i - 1] <= 126)
			&& data->pars->fs != 1)
			line = move_quote_backward(data, line, i);
		else if ((line [i] == '"' && data->pars->fdb == 1)
			&& !(line[i + 1] >= '!' && line[i + 1] <= 126)
			&& data->pars->fs != 1)
			data->pars->fdb = 0;
		if ((line[i] == '\'' && data->pars->fs == 0) && data->pars->fdb != 1)
			data->pars->fs = 1;
		else if ((line [i] == '\'' && data->pars->fs == 1)
			&& data->pars->fdb != 1)
			data->pars->fs = 0;
		if (line[i])
			i++;
	}	
}*/



