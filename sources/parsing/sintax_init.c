/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:35:20 by dgargant          #+#    #+#             */
/*   Updated: 2025/03/27 12:32:27 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

int	get_state(int prev, int pos)
{
	const int matrix[][6] = {
		{}
	};
	return (matrix[prev][pos]);
}

int	check_state(int prev, char c)
{
	int	pos;

	pos = 0;
	if (ft_isalnum(c))
		pos = 1;
	else if (ft_isprint(c) && !ft_isspace(c) && !ft_ispipe(c) && !is_redir(c))
		pos = 2;
	if (ft_ispipe(c))
		pos = 3;
	if (is_redir_in(c) && prev != 4)
		pos = 4;
	else if (is_redir(c) && prev == 4)
		pos = 5;
	else if (is_redir(c) && prev == 5)
		pos = 0;
	return (get_state(prev, pos));
}

int	ft_check_syntax(char *line)
{
	int	i;
	int	state;

	state = 0;
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
