/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:22:25 by pavicent          #+#    #+#             */
/*   Updated: 2025/05/08 13:22:27 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

void	free_lists(t_cmds *lst)
{
	t_cmds	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp)
		{
			if (tmp->s_files)
				ft_free_s_files(tmp->s_files);
			if (tmp->cmds)
				ft_free_void_array((void **)tmp->cmds);
		}
		free(tmp);
		tmp = NULL;
	}
}

void	ft_free_struct(t_pipes *data)
{
	/*int	i;

	i = 0;
	if (data->fd)
	{
		while (data->fd[i])
		{
			free(data->fd[i]);
			i++;
		}
		free(data->fd);
	}*/
	/*if (data->mode == 3)
	{
		if (access(data->cmds->file, F_OK) == 0)
			unlink(data->cmds->file);
	}*/
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	///free_fd(data);
	if (data->cmds)
	{
		free_lists(data->cmds);
		data->cmds = NULL;
	}
	reset_int(data);
	//free(data);
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
