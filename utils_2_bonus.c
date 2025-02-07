/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:41:03 by pavicent          #+#    #+#             */
/*   Updated: 2024/10/15 13:41:05 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	do_fork(t_pipes *data, int i)
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

void	init_outflags(t_lists *lst, t_lists *first)
{
	if (first->docs->flag == 1)
		lst->docs->flag = 3;
	else
		lst->docs->flag = 4;
}

void	check_fd_in(int *fd)
{
	if (*fd > 0)
		return ;
	else
	{
		*fd = open("/dev/null", O_RDONLY);
		if (*fd == -1)
			exit(EXIT_FAILURE);
	}
}

int	add_list(t_lists *list)
{
	t_lists	*new;
	t_lists	*tmp;

	tmp = list;
	new = (t_lists *)malloc(sizeof(t_lists));
	if (!new)
		return (1);
	new->docs = (t_docs *)malloc(sizeof(t_docs));
	if (!new->docs)
		return (1);
	new->docs->fd = -1;
	new->docs->cmd = NULL;
	new->docs->file = NULL;
	new->next = NULL;
	while (list->next)
		list = list->next;
	list->next = new;
	list = tmp;
	return (0);
}
