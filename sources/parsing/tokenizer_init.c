
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
	int	j;
	int	ini;
	char	*cmd;
	char	*tmp;

	j = data->pars->i;
	while (ft_isspace(line[j]))
		j++;
	ini = j;
	while (line[j] && ft_isprint(line[j]) && !ft_isspace(line[j]) && line[j] != '|'
		&& line[j] != '<' && line[j] != '>' && line[j] != '"' && line[j] != '\'')
	{
		j++;
	}
	data->pars->i = j;
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

void set_files(t_pipes*data, char *line, int mode)
{
	data->pars->i++;
	if (line[data->pars->i] == '"' || line[data->pars->i] == '\'')
		take_quote(data, line, line[data->pars->i], mode);
	else
		take_pr(data, line, mode);
}

/* Esto sera una funcion que recorrera la linea
y la tokenizara llamando a otras funciones*/
void	tokenizer_init(t_pipes *data, char *line)
{
	take_first_token(data, line);
	while (line[data->pars->i])
	{
		if (line[data->pars->i] == '"' || line[data->pars->i] == '\'')
			take_quote(data, line, line[data->pars->i], N_NF);
		else if (line[data->pars->i] == '<' && line[data->pars->i + 1] == '<')
		{
			data->pars->i++;
			set_files(data, line, N_HRD);
			//take_hdelimiter(data, line);
		}
		else if (line[data->pars->i] == '>' && line[data->pars->i + 1] == '>')
		{
			data->pars->i++;
			set_files(data, line, N_AOUTF);
			//take_tfile(data, line, N_AOUTF);
		}
		else if (line[data->pars->i] == '<')
			set_files(data, line, N_INF);
		else if (line[data->pars->i] == '>')
			set_files(data, line, N_OUTF);
		else if (line[data->pars->i] == '|')
			take_pipes(data, line);
		else if (ft_isprint(line[data->pars->i]))
			take_pr(data, line, N_NF);
		if (line[data->pars->i])
			data->pars->i++;
	}
}

char	*take_quote2(t_pipes *data, char *line, char *cmd, int j)
{
	char	*cmd2;
	int		ini;

	ini = j;
	if (data->pars->c == '"' || data->pars->c == '\'')
	{
		printf(" ''' line[j]:%c\n", line[j]);
		ini = ++j;
		while (line[j] && line[j] != data->pars->c)
			j++;
	}
	else
	{
		printf("line[j]:%c\n", line[j]);
		while (line[j] && ft_isprint(line[j]) && !ft_isspace(line[j]) && line[j] != '|' && line[j] != '<' && line[j] != '>'
			&& line[j] != '"' && line[j] != '\'')
			j++;
	}
	cmd2 = ft_substr(line, ini, (j - ini));
	cmd = ft_strjoin_free2(cmd, cmd2);
	if (line[j] == '"' || line[j] == '\'')
		j++;
	data->pars->i = j - 1;
	if ((line[j] == '\'' || line[j] == '"') || (ft_isprint(line[j]) 
		&& !ft_isspace(line[j]) && line[j] != '|' && line[j] != '<' && line[j] != '>'))
	{
		data->pars->c = line[j];
		cmd = take_quote2(data, line, cmd, j);
	}
	return (cmd);
}

void	take_quote(t_pipes *data, char *line, char c, int mode)
{
	int 	j;
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
	while (line[j] && ft_isprint(line[j]) && !ft_isspace(line[j]) && line[j] != '|' && line[j] != '<' && line[j] != '>'
		&& line[j] != '"' && line[j] != '\'')
		j++;
	data->pars->i = j - 1;
	cmd2 = ft_substr(line, ini, (j - ini));
	cmd = ft_strjoin_free2(cmd, cmd2);
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
