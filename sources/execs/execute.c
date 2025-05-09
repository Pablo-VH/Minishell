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

void	delete_hd(t_pipes *data)
{
	int		i;
	int		j;
	t_cmds	*tmp;

	i = 0;
	tmp = data->cmds;
	while (i < data->num_cmds)
	{
		j = 0;
		while (data->cmds->s_files && data->cmds->s_files->file && data->cmds->s_files->file[j])
		{
			if (data->cmds->s_files->flagfd[j] == N_HRD
				&& access(data->cmds->s_files->file[j], F_OK) == 0)
				unlink(data->cmds->s_files->file[j]);
			j++;
		}
		data->cmds = data->cmds->next;
		i++;
	}
	data->cmds = tmp;
}

void	wait_pids(t_pipes *data, int i)
{
	while (i < data->num_cmds)
	{
		if (data->pids)
		{
			if (i == data->num_cmds -1)
				waitpid(data->pids[i], &data->status, 0);
			else
				waitpid(data->pids[i], NULL, 0);
		}
		i++;
	}
	if (WIFEXITED(data->status))
		g_exit_status = WEXITSTATUS(data->status);
	else if (WIFSIGNALED(data->status))
		g_exit_status = WTERMSIG(data->status) + 128;
}

static void	open_files(t_pipes *data)
{
	int		i;
	t_cmds	*tmp;
	int		stop;

	tmp = data->cmds;
	while (data->cmds)
	{
		stop = 0;
		i = 0;
		while (data->cmds->s_files && data->cmds->s_files->file && data->cmds->s_files->file[i] && stop == 0)
		{
			if (data->cmds->s_files->flagfd[i] == N_INF)
				stop = infile(data, i);
			if (data->cmds->s_files->flagfd[i] == N_OUTF)
				stop = outfile(data, i);
			if (data->cmds->s_files->flagfd[i] == N_AOUTF)
				stop = append(data, i);
			i++;
		}
		data->cmds = data->cmds->next;
	}
	data->cmds = tmp;
}

static int	open_heredocs(t_pipes *data)
{
	int		i;
	t_cmds	*tmp;
	int		stop;

	tmp = data->cmds;
	stop = 0;
	while (data->cmds)
	{
		stop = 0;
		i = 0;
		while (data->cmds && data->cmds->s_files && data->cmds->s_files->file
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
	if (!data->stop_exec_hd)
	{
		printf("check numcmds: %d\n", data->num_cmds);
		if (data->num_cmds == 1)
		{
			if (check_builtin(data, 0) == 1)
				return ;
		}
		cmds_exec(data);
	}
	delete_hd(data);
}
