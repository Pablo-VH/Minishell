/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:54:17 by pavicent          #+#    #+#             */
/*   Updated: 2024/12/17 10:55:11 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pid(t_pipes **data)
{
	(*data)->pids = malloc(sizeof(pid_t) * ((*data)->num_cmds));
	if (!(*data)->pids)
	{
		perror("malloc pids");
		ft_free_struct(*data);
		return (1);
	}
	if (init_fd(*data))
		return (1);
	return (0);
}

int	init_fd(t_pipes *data)
{
	int	i;

	i = 0;
	data->fd = ft_calloc(data->num_cmds, sizeof(int *));
	while (i < data->num_cmds - 1)
	{
		data->fd[i] = ft_calloc(2, sizeof(int));
		if (data->fd[i] == NULL || (pipe(data->fd[i]) == -1))
		{
			perror("malloc fd or pipe");
			ft_free_struct(data);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_list(t_pipes *data)
{
	int		i;
	t_lists	*tmp;

	i = 1;
	data->list = (t_lists *)malloc(sizeof(t_lists));
	data->list->docs = (t_docs *)malloc(sizeof(t_docs));
	if (!data->list)
	{
		ft_free_struct(data);
		return (1);
	}
	data->list->next = NULL;
	data->list->docs->fd = -1;
	tmp = data->list;
	while (i < data->num_cmds)
	{
		if (add_list(data->list))
		{
			ft_free_struct(data);
			return (1);
		}
		i++;
	}
	data->list = tmp;
	return (0);
}
