/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:35:20 by dgargant          #+#    #+#             */
/*   Updated: 2025/04/07 17:21:46 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

int	get_state(int prev, int pos)
{
	const int matrix[][9] = {
		{1, 2, 3, 4, 5, 6, 7, 8}, // 0 init
		{1, 1, 1, 1, 1, 1}, // 1 error
		{1, 0, 2, 2, 2, 2}, // 2 double quote
		{1, 0, 3, 3, 3, 3}, // 3 single quote
		{1, 2, 4, 4, 4, 4}, // 4 alnum
		{1, 2, 5, 5, 5, 5}, // 5 is_print
		{1, 2, 6, 6, 6, 6}, // 6 pipe
		{1, 2, 7, 7, 7, 7}, // 7 redir_in
		{1, 2, 8, 8, 8, 8}, //8 redir_out
		{1, 2, 9, 9, 9, 9}  // 9 redir_in_out
	};
	return (matrix[prev][pos]);
}

int	check_state(int prev, char c)
{
	int	pos;

	pos = 0;
	if (c == '"')
		pos = 1;
	if (c == '\'')
		pos = 2;
	if (ft_isspace(c))
		pos = 3;
	if (ft_isalnum(c))
		pos = 4;
	else if (ft_isprint(c) && !ft_isspace(c) && !ft_ispipe(c) && !is_redir(c))
		pos = 5;
	if (c == '|')
		pos = 6;
	if (c == '<' && prev != 7)// && prev != 5)
		pos = 7;
	else if (c == '<' && prev == 7)
		pos = 9;
	if (c == '>')
		pos = 8;
	else if (c == '>' && prev == 8)
		pos = 0;
	/*else if (is_redir(c) && prev == 4)
		pos = ;
	else if (is_redir(c) && prev == 5)
		pos = 0;*/
	return (get_state(prev, pos));
}

int	ft_check_syntax(char *line)
{
	int	i;
	int	state;

	state = 0;
	i = 0;
	while (line[i])
	{
		state = choose_state(state, line[i]);
		if (state == 1)
			return (1);
		i++;
	}
	i++;
	return (0);
}


void	reset_quotes(t_pipes *data)
{
	data->pars->fs = 0;
	data->pars->fdb = 0;
}


/*Esto sera retocado en el futuro, recordar que hay que tener mas cosas
en cuenta en la sintaxis*/
int	check_quotes(t_pipes *data, char *line)
{
	int	i;

	i = 0;
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
		i++;
	}
	if (data->pars->fdb || data->pars->fs)
	{
		reset_quotes(data);
		printf(RED"ERROR\n"RESET);
		return (1);
	}
	reset_quotes(data);
	return (0);
}

//recordar insertar funciones en el .h y el makefile
int	sintax_init(t_pipes *data, char *line)
{
	if (line[0] == '\0')
		return (1);
	if (check_quotes(data, line))
		return (1);
	if (check_status(line))
		return (1);
	return (0);
}
