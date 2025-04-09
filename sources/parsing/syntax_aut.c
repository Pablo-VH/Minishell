/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_aut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:10:37 by pavicent          #+#    #+#             */
/*   Updated: 2025/04/08 10:10:39 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

int	get_state(int prev, int pos)
{
	const int	matrix[][8] = {
	{A_ERR, A_INI, A_PRI, A_DOB, A_SIN, A_ERR, A_RIN, A_ROU}, // 0 A_INI
	{A_ERR, A_ERR, A_ERR, A_ERR, A_ERR, A_ERR, A_ERR, A_ERR}, // 1 A_ERR
	{A_ERR, A_SPA, A_PRI, A_DOB, A_SIN, A_PIP, A_RIN, A_ROU}, // 2 A_SPA
	{A_ERR, A_SPA, A_PRI, A_DOB, A_SIN, A_PIP, A_RIN, A_ROU}, // 3 A_PRI
	{A_ERR, A_DOB, A_DOB, A_SPA, A_DOB, A_DOB, A_DOB, A_DOB}, // 4 A_DOB
	{A_ERR, A_SIN, A_SIN, A_SIN, A_SPA, A_SIN, A_SIN, A_SIN}, // 5 A_SIN
	{A_ERR, A_PIP, A_PRI, A_DOB, A_SIN, A_ERR, A_RIN, A_ROU}, // 6 A_PIP
	{A_ERR, A_RIN, A_PRI, A_DOB, A_SIN, A_ERR, A_RIO, A_ERR}, // 7 A_RIN
	{A_ERR, A_ROU, A_PRI, A_DOB, A_SIN, A_ERR, A_ERR, A_RIO}, // 8 A_ROU
	{A_ERR, A_RIO, A_PRI, A_DOB, A_SIN, A_ERR, A_ERR, A_ERR}, // 9 A_RIO
	{0}, //err space  all 	"      '	  |      <      >
	};

	return (matrix[prev][pos]);
}

int	check_state(int prev, char c)
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
		state = check_state(state, line[i]);
		if (state == 1)
		{
			printf(RED"ERROR\n"RESET);
			return (1);
		}
		i++;
	}
	if (state > 3)
	{
		printf(RED"ERROR\n"RESET);
		return (1);
	}
	return (0);
}

int	syntax_init(char *line)
{
	if (line[0] == '\0')
		return (1);
	if (ft_check_syntax(line))
		return (1);
	return (0);
}
