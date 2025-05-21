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

/*int	ft_check_syntax(char *line)
{
	int	i;
	int	state;

	state = 0;
	i = 0;
	while (line[i])
	{
		state = check_state(state, line[i]);
		if (state == 1)
		{
			printf(RED"syntax error near unexpected token\n"RESET);
			g_exit_status = 2;
			return (1);
		}
		i++;
	}
	if (state > 3)
	{
		printf(RED"syntax error near unexpected token\n"RESET);
		g_exit_status = 2;
		return (1);
	}
	return (0);
}*/

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
	//printf("numcmds::::::%d\n", data->pars->ncmds[data->pars->np]);
	data->pars->np++;
}
void	token_count_files(t_pipes *data, char *line)
{
	int	i;
	int	state;
	int	prev;
	t_cmds	*tmp;

	i = data->pars->count_f;
	state = 0;
	tmp = data->cmds;
	tmp = ft_lstlast(tmp);
	if (!line)
		return ;
	if (line[i] == '|')
		i++;
	while (line[i])
	{
		prev = state;
		state = ft_token_state(state, line[i]);
	//	printf("line[i] = %c; state:%d\n", line[i], state);
		if ((state == 7 || state == 8) && (prev != 7 && prev != 8))
			tmp->s_files->nfiles++;
		if (state == 6)
		{
			data->pars->count_f = i;
		//	printf("%d\n", tmp->s_files->nfiles);
			return (take_node_files(tmp));
		}
		i++;
	}
	take_node_files(tmp);
}
