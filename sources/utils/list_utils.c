/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:00:05 by dgargant          #+#    #+#             */
/*   Updated: 2025/05/07 10:08:27 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

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

t_cmds	*ft_lstlast(t_cmds *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_cmds *lst, t_cmds *new)
{
	t_cmds	*puntero;

	puntero = ft_lstlast(lst);
	if (!puntero)
		puntero = new;
	else
		puntero->next = new;
}

t_cmds	*ft_lstnew(void)
{
	t_cmds	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_cmds));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->s_files = ft_calloc(1, sizeof(t_files));
	new_cmd->cmds = NULL;
	new_cmd->stop_exec = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}
