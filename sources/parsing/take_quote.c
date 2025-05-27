/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:07:49 by pavicent          #+#    #+#             */
/*   Updated: 2025/05/27 11:07:50 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

char	*tk_2(t_pipes *data, char *line, char *cmd, int j)
{
	if (line[j] && ((line[j] == '\'' || line[j] == '"') || (ft_isprint(line[j])
				&& !ft_isspace(line[j]) && line[j] != '|' && line[j] != '<'
				&& line[j] != '>')))
	{
		data->pars->c = line[j];
		cmd = take_quote2(data, line, cmd, j);
	}
	return (cmd);
}

char	*take_quote2(t_pipes *data, char *line, char *cmd, int j)
{
	char	*cmd2;
	int		ini;

	ini = j;
	if (data->pars->c == '"' || data->pars->c == '\'')
	{
		ini = ++j;
		while (line[j] && line[j] != data->pars->c)
			j++;
		cmd2 = ft_substr(line, ini, (j - ini));
		data->pars->i = j;
		j++;
	}
	else
	{
		while (line[j] && ft_isprint(line[j]) && !ft_isspace(line[j])
			&& line[j] != '|' && line[j] != '<' && line[j] != '>'
			&& line[j] != '"' && line[j] != '\'')
			j++;
		data->pars->i = j;
		cmd2 = ft_substr(line, ini, (j - ini));
	}
	cmd = ft_strjoin_free2(cmd, cmd2);
	cmd = tk_2(data, line, cmd, j);
	return (cmd);
}

void	tk_q(t_pipes *data, char *cmd, char *line, int mode)
{
	int	j;

	j = data->pars->i + 1;
	if (line[j] == '\'' || line[j] == '"')
	{
		data->pars->c = line[j];
		cmd = take_quote2(data, line, cmd, j);
	}
	if (mode == N_NF)
		insert_cmds(data, cmd);
	else
		set_node_files(data, cmd, mode);
}

void	take_quote(t_pipes *data, char *line, char c, int mode)
{
	int		j;
	char	*cmd;
	int		ini;
	char	*cmd2;

	data->pars->i++;
	j = data->pars->i;
	while (line [j] && line[j] != c)
		j++;
	cmd = ft_substr(line, data->pars->i, (j - data->pars->i));
	if (line[j])
		j++;
	ini = j;
	while (line[j] && ft_isprint(line[j]) && !ft_isspace(line[j])
		&& line[j] != '|' && line[j] != '<' && line[j] != '>'
		&& line[j] != '"' && line[j] != '\'')
		j++;
	data->pars->i = j - 1;
	cmd2 = ft_substr(line, ini, (j - ini));
	cmd = ft_strjoin_free2(cmd, cmd2);
	tk_q(data, cmd, line, mode);
}
