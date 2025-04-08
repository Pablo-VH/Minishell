/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:24:31 by pavicent          #+#    #+#             */
/*   Updated: 2024/10/30 12:24:33 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

void	close_pipes(t_pipes *data, int i)
{
	while (i < data->num_cmds - 1)
	{
		if (data->fd[i])
		{
			close(data->fd[i][0]);
			close(data->fd[i][1]);
			free(data->fd[i]);
		}
		i++;
	}
	if (data->fd)
		free(data->fd);
}

void	pipes_redirs(t_pipes *data, int i, t_cmds *list)
{
	if (i > 0)
	{
		if (dup2(data->fd[i - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2 failed");
			close_pipes(data, 0);
			close_files(list);
			ft_free_struct(data);
			exit(1);
		}
	}
	if (i < data->num_cmds -1)
	{
		if (dup2(data->fd[i][1], STDOUT_FILENO) == -1)
		{
			perror("dup2 failed");
			close_pipes(data, 0);
			close_files(list);
			ft_free_struct(data);
			exit(1);
		}
	}
	close_pipes(data, 0);
}

void	duplication(t_pipes *data, int i, int std, t_cmds *list)
{
	if (data->cmds->s_files->fd[i] < 0)
	{
		perror("bad fd");
		close_files(list);
		ft_free_struct(data);
		exit(1);
	}
	if (dup2(data->cmds->s_files->fd[i], std) == -1)
	{
		perror("dup2 failed");
		close_files(list);
		ft_free_struct(data);
		exit(1);
	}
	close(data->cmds->s_files->fd[i]);
	data->cmds->s_files->fd[i] = -1;
}

void	redir_files(t_pipes *data, t_cmds *list)
{
	int	i;

	i = 0;
	if (data->cmds && data->cmds->s_files && data->cmds->s_files->file[i])
	{
		if (data->cmds->s_files->flagfd[i] == N_INF
			|| data->cmds->s_files->flagfd[i] == N_HRD)
			duplication(data, i, STDIN_FILENO, list);
		else if (data->cmds->s_files->flagfd[i] == N_OUTF
			|| data->cmds->s_files->flagfd[i] == N_AOUTF)
			duplication(data, i, STDOUT_FILENO, list);
		i++;
	}
}
