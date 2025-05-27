/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_counters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:40:00 by dgargant          #+#    #+#             */
/*   Updated: 2025/05/06 11:10:02 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

void	count_heredocs(t_pipes *data, char *line)
{
	int	i;

	i = 0;
	data->pars->h_doc = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] != '"')
				i++;
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				i++;
		}
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			data->nhrd = ++data->pars->h_doc;
			i++;
		}
		i++;
	}
}

void	count_pipes(t_pipes *data, char *line)
{
	int	i;
	int	npipe;

	i = 0;
	npipe = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] != '"')
				i++;
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				i++;
		}
		else if (line[i] == '|' )
			data->npipes = ++npipe;
		i++;
	}
}

int	ft_is_token(char *line, int i)
{
	return ((line[i] == '<' || line[i] == '>')
		|| (line[i] == '<' && line[i + 1] == '<')
		|| (line[i] == '>' && line[i + 1] == '>'));
}
