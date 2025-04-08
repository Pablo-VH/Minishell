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
int	syntax_init(t_pipes *data, char *line)
{
	if (line[0] == '\0')
		return (1);
	if (check_quotes(data, line))
		return (1);
	if (ft_check_syntax(line))
		return (1);
	return (0);
}
