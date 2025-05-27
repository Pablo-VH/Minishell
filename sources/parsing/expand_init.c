/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:39:05 by dgargant          #+#    #+#             */
/*   Updated: 2025/05/27 10:00:12 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

void	exp_her(char *line, int *i)
{
	(*i) += 2;
	while (!(line[*i] >= '!' && line[*i] <= 126))
		(*i) += 1;
	while (line[*i])
	{
		if (line[*i] == '<' || line[*i] == '>' || line[*i] == '|')
			break ;
		if (!(line[*i] >= '!' && line[*i] <= 126))
			break ;
		(*i) += 1;
	}
}

void	pre_exp_dol(t_pipes *data, char *line, int *i)
{
	if ((line[*i] == '"' && data->pars->fdb == 0) && data->pars->fs != 1)
		data->pars->fdb = 1;
	else if ((line [data->pars->ei] == '"' && data->pars->fdb == 1)
		&& data->pars->fs != 1)
		data->pars->fdb = 0;
	if ((line[*i] == '\'' && data->pars->fs == 0) && data->pars->fdb != 1)
		data->pars->fs = 1;
	else if ((line[*i] == '\'' && data->pars->fs == 1) && data->pars->fdb != 1)
		data->pars->fs = 0;
	if (line[*i] == '<' && line[(*i) + 1] == '<')
		exp_her(line, i);
	if (line[*i] == '$' && (ft_isspace(line[(*i) + 1]) || !line[(*i) + 1]))
		(*i) += 1;
	if (line[*i] == '$' && (line[(*i) + 1] == '"' || ft_isspace(line[(*i) + 1]))
		&& line[(*i) + 1] && (data->pars->fdb == 1))
		(*i) += 1;
	if (line[(*i) + 1] && (line[(*i) + 1] == '"' || line[(*i) + 1] == '\'')
		&& data->pars->fdb == 1)
		(*i) += 1;
}

void	post_exp_dol(t_pipes *data, char *line)
{
	if (line[data->pars->ei])
		data->pars->ei++;
	if (data->pars->p_exp > -1)
	{
		data->pars->ei = data->pars->p_exp;
		data->pars->p_exp = -1;
	}
}

char	*expand_init(t_pipes *data, char *line)
{
	char	*new_line;
	char	*var;
	char	*exp;

	data->pars->ei = 0;
	new_line = NULL;
	var = NULL;
	exp = NULL;
	data->pars->p_exp = -1;
	while (line[data->pars->ei])
	{
		pre_exp_dol(data, line, &data->pars->ei);
		if (line[data->pars->ei] == '$' && (data->pars->fs == 0))
		{
			var = take_v(data, line, data->pars->ei);
			exp = search_in_env(data, var);
			new_line = insert_expansion(data, line, var, exp);
			free(line);
			line = NULL;
			line = new_line;
		}
		post_exp_dol(data, line);
	}
	return (line);
}

char	*take_v( t_pipes *data, char *line, int i)
{
	int		j;
	char	*new_v;

	j = 0;
	new_v = NULL;
	if (!line[i + 1] || ft_isspace(line[i + 1]))
	{
		j = i + 1;
		new_v = ft_substr(line, i, 2);
	}
	else if (line[i + 1] && (line[i + 1] == '"' || line[i + 1] == '\''))
	{
		data->pars->p_exp = i;
		return (NULL);
	}
	else
	{
		i++;
		j = i;
		while (line[j] && !ft_isspace(line[j]) && !ft_is_token(line, j)
			&& line[j] != '|' && line[j] != '"' && line[j] != '\'')
			j++;
		new_v = ft_substr(line, i, (j - i));
	}
	return (new_v);
}
