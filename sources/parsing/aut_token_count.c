/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aut_token_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:45:48 by pavicent          #+#    #+#             */
/*   Updated: 2025/05/19 13:45:51 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

int	get_state_tk(int prev, int pos)
{
	const int	matrix[][8] = {
	{T_ERR, T_INI, T_PRI, T_DOB, T_SIN, T_ERR, T_RIN, T_ROU}, // 0 T_INI
	{T_ERR, T_ERR, T_ERR, T_ERR, T_ERR, T_ERR, T_ERR, T_ERR}, // 1 T_ERR
	{T_ERR, T_SPA, T_PRI, T_DOB, T_SIN, T_PIP, T_RIN, T_ROU}, // 2 T_SPA
	{T_ERR, T_SPA, T_PRI, T_DOB, T_SIN, T_PIP, T_RIN, T_ROU}, // 3 T_PRI
	{T_ERR, T_DOB, T_DOB, T_COM, T_DOB, T_DOB, T_DOB, T_DOB}, // 4 T_DOB
	{T_ERR, T_SIN, T_SIN, T_SIN, T_COM, T_SIN, T_SIN, T_SIN}, // 5 T_SIN
	{T_ERR, T_SPA, T_PRI, T_DOB, T_SIN, T_ERR, T_RIN, T_ROU}, // 6 T_PIP
	{T_ERR, T_RIN, T_PRI, T_DOB, T_SIN, T_ERR, T_RIN, T_ERR}, // 7 T_RIN
	{T_ERR, T_ROU, T_PRI, T_DOB, T_SIN, T_ERR, T_ERR, T_ERR}, // 8 T_ROU
	{T_ERR, T_SPA, T_PRI, T_DOB, T_SIN, T_PIP, T_RIN, T_ROU}, // 9 T_COM
	{0}, //err space  all 	"      '	  |      <      >
	};

	return (matrix[prev][pos]);
}

int	ft_token_state(int prev, char c)
{
	int	pos;

	pos = 0;
	if (ft_isspace(c))
		pos = 1;
	else if (ft_isprint(c) && !ft_isspace(c) && c != '|' && c != '<' && c != '>'
		&& c != '"' && c != '\'')
		pos = 2;
	else if (c == '"')
		pos = 3;
	else if (c == '\'')
		pos = 4;
	else if (c == '|')
		pos = 5;
	else if (c == '<')
		pos = 6;
	else if (c == '>')
		pos = 7;
	return (get_state_tk(prev, pos));
}

void	take_node_files(t_cmds	*nd)
{
	nd->s_files->file = ft_calloc(nd->s_files->nfiles + 1, sizeof(char *));
	nd->s_files->flagfd = ft_calloc(nd->s_files->nfiles + 1, sizeof(int));
}

void	token_count_cmds(t_pipes *data, char *line)
{
	int	i;
	int	state;
	int	prev;

	i = data->pars->count;
	state = 0;
	if (!line)
		return ;
	if (line[i] == '|')
		i++;
	while (line[i])
	{
		prev = state;
		state = ft_token_state(state, line[i]);
		if (prev <= 2 && state > 2 && state < 6)
			data->pars->ncmds[data->pars->np]++;
		if (state == 6)
		{
			data->pars->np++;
			data->pars->count = i;
			return ;
		}
		i++;
	}
	data->pars->np++;
}

void	token_count_files(t_pipes *data, char *line)
{
	int	state;
	int	prev;

	state = 0;
	data->tmp = data->cmds;
	data->tmp = ft_lstlast(data->tmp);
	if (!line)
		return ;
	if (line[data->pars->count_f] == '|')
		data->pars->count_f++;
	while (line[data->pars->count_f])
	{
		prev = state;
		state = ft_token_state(state, line[data->pars->count_f]);
		if ((state == 7 || state == 8) && (prev != 7 && prev != 8))
			data->tmp->s_files->nfiles++;
		if (state == 6)
			return (take_node_files(data->tmp));
		data->pars->count_f++;
	}
	take_node_files(data->tmp);
}
