/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:43:27 by dgargant          #+#    #+#             */
/*   Updated: 2025/05/06 11:11:25 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

void	take_pipes(t_pipes *data, char *line)
{
	int	i;

	i = data->pars->i + 1;
	data->pars->count = i;
	token_count_cmds(data, line);
	take_token(data);
	data->pars->np2 = 0;
	data->pars->c_cmd++;
	token_count_files(data, line);
}
