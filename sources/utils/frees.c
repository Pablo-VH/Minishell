/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:47:10 by pavicent          #+#    #+#             */
/*   Updated: 2025/02/07 08:53:25 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

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
	/*if (data->mode == 3)
	{
		if (access(data->cmds->file, F_OK) == 0)
			unlink(data->cmds->file);
	}*/
	if (data->pids)
		free(data->pids);
	free_fd(data);
	if (data->cmds)
		free_lists(data->cmds);
	//if (data->limiters)
	//	free(data->limiters);
	free(data);
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

void	free_lists(t_cmds *lst)
{
	t_cmds	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp)
		{
			/*if (tmp->file)
				free(tmp->file);*/
			if (tmp->cmd)
				free(tmp->cmd);
		}
		free(tmp);
	}
}

/*void	close_files(t_cmds *list)
{
	t_cmds	*tmp;

	tmp = list;
	while (list)
	{
		if (list->fd > 0)
			close(list->fd);
		list = list->next;
	}
	list = tmp;
}*/
