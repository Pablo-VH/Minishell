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
	const int	matrix[][7] = {
	{A_ERR, A_DOB, A_SIN, A_SPA, A_PRI, A_ERR, A_RIN, A_ROU}, // 0 A_INI
	{A_ERR, A_ERR, A_ERR, A_ERR, A_ERR, A_ERR, A_ERR, A_ERR}, // 1 A_ERR
	{A_ERR, A_INI, A_DOB, A_DOB, A_DOB, A_DOB, A_DOB, A_DOB}, // 2 A_DOB
	{A_ERR, A_INI, A_SIN, A_SIN, A_SIN, A_SIN, A_SIN, A_SIN}, // 3 A_SIN
	{A_ERR, A_DOB, A_SIN, A_PRI, A_PRI, A_PIP, A_RIN, A_ROU}, // 4 A_SPA
	{A_ERR, A_DOB, A_SIN, A_SPA, A_PRI, A_ERR, A_RIN, A_ROU}, // 5 A_PRI
	{A_ERR, A_DOB, A_SIN, A_PIP, A_PRI, A_ERR, A_RIN, A_ROU}, // 6 A_PIP
	{A_ERR, A_DOB, A_SIN, A_RIN, A_PRI, A_ERR, A_RIO, A_ERR}, // 7 A_RIN
	{A_ERR, A_DOB, A_SIN, A_RIN, A_PRI, A_ERR, A_ERR, A_RIO}, // 8 A_ROU
	{A_ERR, A_DOB, A_SIN, A_RIO, A_PRI, A_ERR, A_ERR, A_ERR}, // 9 A_RIO
	};

	return (matrix[prev][pos]);
}

int	check_state(int prev, char c)
{
	int	pos;

	pos = 0;
	if (c == '"')
		pos = 1;
	else if (c == '\'')
		pos = 2;
	else if (ft_isspace(c))
		pos = 3;
	else if (ft_isprint(c) && !ft_isspace(c) && !ft_ispipe(c) && !is_redir(c))
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
		state = choose_state(state, line[i]);
		if (state == 1)
			return (1);
		i++;
	}
	if (state > 5)
		return (1);
	return (0);
}
