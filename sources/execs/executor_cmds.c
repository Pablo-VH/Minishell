/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:40:29 by pavicent          #+#    #+#             */
/*   Updated: 2025/03/08 12:40:31 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

static int	init_pfd(t_pipes *data)
{
	int	i;

	i = 0;
	data->fd = ft_calloc(data->num_cmds, sizeof(int *));
	if (data->fd == NULL)
	{
		perror("malloc pfd");
		return (1);
	}
	while (i < data->num_cmds - 1)
	{
		data->fd[i] = ft_calloc(2, sizeof(int));
		if (data->fd[i] == NULL || (pipe(data->fd[i]) == -1))
		{
			perror("malloc pfd or pipe");
			if (data->pids)
				free(data->pids);
			ft_free_void_array((void **)data->fd);
			return (1);
		}
		i++;
	}
	return (0);
}
static int	init_pids_n_pipes(t_pipes *data)
{
	data->pids = malloc(sizeof(pid_t) * data->num_cmds);
	if (!data->pids)
	{
		perror("malloc pids");
		return (1);
	}
	if (init_pfd(data))
		return (1);
	return (0);
}

static int	do_fork(t_pipes *data, int i)
{
	data->pids[i] = fork();
	if (data->pids[i] == -1)
	{
		if (data->pids)
			free(data->pids);
		perror("fork");
		close_pipes(data, data->num_cmds);
		return (1);
	}
	return (0);
}

static int	child_process(t_pipes *data, int i, t_cmds *tmp)
{
	if (do_fork(data, i))
		return (1);
	if (data->pids[i] == 0)
	{
		rl_clear_history();
		signal(SIGQUIT, SIG_DFL);
		pipes_redirs(data, i, tmp);
		if (!data->cmds->stop_exec);
			redir_files(data, tmp);
		close_files(tmp);
		if (data->cmds->stop_exec)
		{
			ft_free_all(data);
			exit(1);
		}
		executor(data, tmp);
	}
	return (0);
}

void	cmds_exec(t_pipes *data)
{
	int		i;
	t_cmds	*tmp;

	i = 0;
	tmp = data->cmds;
	if (init_pids_n_pipes(data))
		return ;
	while (i < data->num_cmds)
	{
		if (child_process(data, i, tmp))
			break ;
		signal(SIGINT, SIG_IGN);
		data->cmds = data->cmds->next;
		i++;
	}
	data->cmds = tmp;
	close_pipes(data, 0);
	close_files(data->cmds);
	wait_pids(data, 0);
}
