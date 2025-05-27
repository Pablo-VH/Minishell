/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:17:38 by dgargant          #+#    #+#             */
/*   Updated: 2025/05/06 11:10:37 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

static void	reset_pars(t_pipes *data, char *line)
{
	free(data->pars->ncmds);
	data->pars->ncmds = NULL;
	data->pars->np = 0;
	data->pars->count = 0;
	data->nhrd = 0;
	data->npipes = 0;
	data->pars->c_cmd = 0;
	data->pars->np2 = 0;
	data->pars->fdb = 0;
	data->pars->fs = 0;
	free(line);
	line = NULL;
}

void	file_fd(t_pipes *data)
{
	t_cmds	*tmp;

	tmp = data->cmds;
	while (tmp)
	{
		if (tmp->s_files->nfiles > 0)
			tmp->s_files->fd = ft_calloc(tmp->s_files->nfiles, sizeof(int));
		tmp = tmp->next;
	}
}

void	parsing_init(t_pipes *data, char *rline)
{
	char	*line;

	line = ft_strdup(rline);
	data->pars->c_cmd = 0;
	data->pars->count_f = 0;
	if (syntax_init(line))
	{
		free(line);
		return ;
	}
	line = expand_init(data, line);
	if (!line)
		return ;
	if (ft_strnstr(line, "<<", ft_strlen(line)))
		count_heredocs(data, line);
	if (ft_strnstr(line, "|", ft_strlen(line)))
		count_pipes(data, line);
	data->pars->ncmds = ft_calloc(data->npipes + 2, sizeof(int));
	tokenizer_init(data, line);
	file_fd(data);
	reset_pars(data, line);
}
