/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:07:08 by dgargant          #+#    #+#             */
/*   Updated: 2025/05/06 11:11:07 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

void	insert_cmds(t_pipes *data, char *comand)
{
	t_cmds	*last;

	last = NULL;
	if (data->cmds)
	{
		last = ft_lstlast(data->cmds);
		if (!last->cmds)
		{
			last->cmds = ft_calloc(data->pars->ncmds[data->pars->c_cmd] + 1,
					sizeof(char *));
			last->cmds[data->pars->np2] = comand;
			data->pars->np2++;
		}
		else
		{
			last->cmds[data->pars->np2] = comand;
			data->pars->np2++;
		}
	}
}

void	take_first_token(t_pipes *data, char *line)
{
	token_count_cmds(data, line);
	take_token(data);
	token_count_files(data, line);
}

void	take_token(t_pipes *data)
{
	t_cmds	*cmd;

	cmd = NULL;
	if (!data->cmds)
		data->cmds = ft_lstnew();
	else
	{
		cmd = ft_lstnew();
		ft_lstadd_back(data->cmds, cmd);
	}
	data->num_cmds++;
	data->pars->np2 = 0;
}

void	set_node_files(t_pipes *data, char *file, int flagfd)
{
	int		i;
	t_cmds	*current;

	i = 0;
	current = data->cmds;
	current = ft_lstlast(current);
	while (i < current->s_files->nfiles)
	{
		if (!current->s_files->file[i]
			&& !current->s_files->flagfd[i])
		{
			current->s_files->file[i] = file;
			current->s_files->flagfd[i] = flagfd;
			return ;
		}
		else
			i++;
	}
}
