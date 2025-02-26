/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:57:13 by pavicent          #+#    #+#             */
/*   Updated: 2025/02/10 12:57:15 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "gertru.h"

static int	open_heredocs(t_pipes *data)
{
	int		i;
	t_cmds	*tmp;
	int		stop;

	tmp = data->cmds;
	while (data->cmds)
	{
		stop = 0;
		i = 0;
		while (data->cmds->s_files && data->cmds->s_files->file
			&& data->cmds->s_files->file[i] && stop == 0)
		{
			if (data->cmds->s_files->flagfd[i] == N_HRD)
				stop = heredoc(data, i);
			i++;
		}
		data->cmds = data->cmds->next;
	}
	data->cmds = tmp;
	return (stop);
}

void	execute(t_pipes *data)
{
	int	stop;

	stop = open_heredocs(data);
	if (!stop)
		open_files(data);
	if (data->num_cmds == 1)
	{
		if (check_builtin(data, 0) == 1)
			return ;
	}
	cmds_exec(data);
	delete_hd(data);
}
