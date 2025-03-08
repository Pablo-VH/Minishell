/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:47:10 by pavicent          #+#    #+#             */
/*   Updated: 2024/12/17 12:16:03 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_struct(t_pipes *data)
{
	int	i;

	i = 0;
	if (data->fd)
	{
		while (data->fd[i])
		{
			free(data->fd[i]);
			i++;
		}
		free(data->fd);
	}
	if (data->mode == 3)
	{
		if (access(data->list->docs->file, F_OK) == 0)
			unlink(data->list->docs->file);
	}
	if (data->pids)
		free(data->pids);
	free_fd(data);
	if (data->list)
		free_lists(data->list);
	if (data->limiter)
		free(data->limiter);
	free(data);
}

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
	{
		while (data->fd[i])
		{
			free(data->fd[i]);
			i++;
		}
		free(data->fd);
	}
	data->fd = NULL;
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_lists(t_lists *lst)
{
	t_lists	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->docs)
		{
			if (tmp->docs->file)
				free(tmp->docs->file);
			if (tmp->docs->cmd)
				free(tmp->docs->cmd);
			free(tmp->docs);
		}
		free(tmp);
	}
}

