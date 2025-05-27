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

void	take_pr(t_pipes *data, char *line, int mode)
{
	int		j;
	int		ini;
	char	*cmd;
	char	*tmp;

	j = data->pars->i;
	while (ft_isspace(line[j]))
		j++;
	ini = j;
	while (line[j] && ft_isprint(line[j]) && !ft_isspace(line[j])
		&& line[j] != '|' && line[j] != '<' && line[j] != '>'
		&& line[j] != '"' && line[j] != '\'')
		j++;
	data->pars->i = j - 1;
	cmd = ft_substr(line, ini, (j - ini));
	if (line[j] && (line[j] == '"' || line[j] == '\''))
	{
		data->pars->c = line[j];
		tmp = cmd;
		cmd = take_quote2(data, line, cmd, j);
	}
	if (mode == N_NF)
		insert_cmds(data, cmd);
	else
		set_node_files(data, cmd, mode);
}

void	set_files(t_pipes*data, char *line, int mode)
{
	data->pars->i++;
	if (line[data->pars->i] == '"' || line[data->pars->i] == '\'')
		take_quote(data, line, line[data->pars->i], mode);
	else
		take_pr(data, line, mode);
}

void	toke_2(t_pipes *data, char *line)
{
	if (line[data->pars->i] == '>' && line[data->pars->i + 1] != '>')
		set_files(data, line, N_OUTF);
	else if (ft_isprint(line[data->pars->i])
		&& !ft_isspace(line[data->pars->i]) && line[data->pars->i] != '|'
		&& line[data->pars->i] != '<' && line[data->pars->i] != '>'
		&& line[data->pars->i] != '"' && line[data->pars->i] != '\'')
		take_pr(data, line, N_NF);
}

void	tokenizer_init(t_pipes *data, char *line)
{
	take_first_token(data, line);
	while (line[data->pars->i])
	{
		while (ft_isspace(line[data->pars->i]))
			data->pars->i++;
		if (line[data->pars->i] == '"' || line[data->pars->i] == '\'')
			take_quote(data, line, line[data->pars->i], N_NF);
		else if (line[data->pars->i] == '<' && data->pars->i >= 1
			&& line[data->pars->i - 1] == '<')
			set_files(data, line, N_HRD);
		else if (line[data->pars->i] == '>' && data->pars->i >= 1
			&& line[data->pars->i - 1] == '>')
			set_files(data, line, N_AOUTF);
		else if (line[data->pars->i] == '<' && line[data->pars->i + 1] != '<')
			set_files(data, line, N_INF);
		else
			toke_2(data, line);
		if (line[data->pars->i] == '|')
			take_pipes(data, line);
		if (line[data->pars->i])
			data->pars->i++;
	}
}
