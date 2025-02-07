/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:00:05 by dgargant          #+#    #+#             */
/*   Updated: 2025/02/06 09:13:47 by dgargant         ###   ########.fr       */
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
	if (!lst)
	{
		//write(1, "ii", 2);
	}
	while (lst && lst->next)
	{
		//write(1, "a", 1);
		lst = lst->next;
	}
	return (lst);
}

// añade el nodo al final de la lista
void	ft_lstadd_back(t_cmds *lst, t_cmds *new)
{
	t_cmds	*puntero;

	puntero = ft_lstlast(lst);
	if (!puntero)
	{
		puntero = new;
		//write(1, "e", 1);
	}
	else
	{
		puntero->next = new;
		//printf("%s...\n", puntero->next->cmd);
	}
}


// crea un nodo de la lista
t_cmds	*ft_lstnew(char *cmd)
{
	t_cmds	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_cmds));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->s_files = ft_calloc(1, sizeof(t_files));
	new_cmd->cmd = cmd;
	new_cmd->next = NULL;
	return (new_cmd);
}


/*t_files	*file_lstlast(t_files *lst)
{
	if (!lst)
	{
		//write(1, "ii", 2);
	}
	while (lst && lst->next)
	{
		//printf("\n");
		lst = lst->next;
	}
	return (lst);
}*/

// añade el nodo al final de la lista
/*void	file_lstadd_back(t_files *lst, t_files *new)
{
	t_files	*puntero;

	puntero = file_lstlast(lst);
	if (!puntero)
	{
		puntero = new;
		//write(1, "e", 1);
	}
	else
	{
		puntero->next = new;
		//printf("%s...\n", puntero->next->cmd);
	}
}*/


// crea un nodo de la lista
/*t_files	*file_lstnew(int flagfd)
{
	t_files	*new_flag;

	new_flag = ft_calloc(1, sizeof(t_files));
	if (new_flag == NULL)
		return (NULL);
	new_flag->flagfd  = flagfd;
	new_flag->next = NULL;
	return (new_flag);
}*/