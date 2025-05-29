/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 09:33:09 by pavicent          #+#    #+#             */
/*   Updated: 2025/05/29 09:33:46 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

int	iter_exp(char *line, int j)
{
	while (line[j] && !ft_isspace(line[j]) && !ft_is_token(line, j)
		&& line[j] != '|' && line[j] != '"' && line[j] != '\''
		&& line[j] != '$')
		j++;
	return (j);
}
