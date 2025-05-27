/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:31:58 by pavicent          #+#    #+#             */
/*   Updated: 2025/05/23 11:31:59 by pavicent         ###   ########.fr       */
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

void	ft_free_struct2(t_pipes *data)
{
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	if (data->cmds)
	{
		free_lists(data->cmds);
		data->cmds = NULL;
	}
	reset_int(data);
}
