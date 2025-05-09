
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:13:37 by dgargant          #+#    #+#             */
/*   Updated: 2025/03/31 12:17:43 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"


/* Esto sera una funcion que recorrera la linea
y la tokenizara llamando a otras funciones*/
void	tokenizer_init(t_pipes *data, char *line)
{
	data->pars->i = 0;
	data->pars->np2 = 0;
	data->pars->c_cmd = 0;
	take_fist_token(data, line);
	while (line[data->pars->i])
	{
		if (line[data->pars->i] == '"')
			take_quote(data, line, '"');
		else if (line[data->pars->i] == '\'')
			take_quote(data, line, '\'');
		else if (line[data->pars->i] == '<' && line[data->pars->i + 1] == '<')
		{
			data->pars->i++;
			take_hdelimiter(data, line);
		} else if (line[data->pars->i] == '>' && line[data->pars->i + 1] == '>')
		{
			data->pars->i++;
			take_tfile(data, line, N_AOUTF);
		}
		else if (line[data->pars->i] == '<')
			take_tfile(data, line, N_INF);
		else if (line[data->pars->i] == '>')
			take_tfile(data, line, N_OUTF);
		else if (line[data->pars->i] == '|')
			take_pipes(data, line);
		else if (line[data->pars->i] >= '!' && line[data->pars->i] <= 126)
		{
			insert_cmds(data,take_cmd(data,line, data->pars->i));
			while (line[data->pars->i])
			{
				if (!line[data->pars->i] || ft_is_token(line, data->pars->i) || line[data->pars->i] == '|'
				|| !(line[data->pars->i] >= '!' && line[data->pars->i] <= 126))
				{
					data->pars->i--;
					break;
				}
				data->pars->i++;
			}
		}
		if (line[data->pars->i])
			data->pars->i++;
	}
}

void	take_quote(t_pipes *data, char *line, char c)
{
	int j;
	char *cmd;

	data->pars->i++;
	j = data->pars->i;
	while (line[j] != c)
		j++;
	cmd = ft_substr(line, data->pars->i, (j - data->pars->i));
	data->pars->i = j;
	insert_cmds(data, cmd);
}