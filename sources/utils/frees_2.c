/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:24:17 by pavicent          #+#    #+#             */
/*   Updated: 2025/05/07 10:14:56 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

void	free_fd(t_pipes *data)
{
	int	i;

	i = 0;
	if (data->fd)
	{
		if (data->fd[i])
		{
			while (data->fd[i])
			{
				free(data->fd[i]);
				i++;
			}
		}
		free(data->fd);
		data->fd = NULL;
	}
}

void	reset_int(t_pipes *data)
{
	//data->mode = 0;
	data->num_cmds = 0;
	data->nhrd = 0;
	data->npipes = 0;
	data->stop_exec_hd = 0;
}

void	ft_free_s_files(t_files *files)
{
	if (files->file)
		ft_free_void_array((void **) files->file);
	if (files->flagfd)
	{
		free(files->flagfd);
		files->flagfd = NULL;
	}
	if (files->fd)
	{
		free(files->fd);
		files->fd = NULL;
	}
	files->nfiles = 0;
	free(files);
	files = NULL;
}

void	ft_free_cmds(t_cmds *list, t_cmds *tmp)
{
	while (list)
	{
		tmp = list;
		if (list->cmds)
			ft_free_void_array((void **)list->cmds);
		if (list->s_files)
			ft_free_s_files(list->s_files);
		list->stop_exec = 0;
		list = list->next;
		free(tmp);
		tmp = NULL;
	}
	free (list);
	list = NULL;
}

void	ft_free_all(t_pipes *data)
{
	if (data->env)
		ft_free_void_array((void **)data->env);
	if (data->pwd)
	{
		free(data->pwd);
		data->pwd = NULL;
	}
	ft_free_pids(&data->pids);
	if (data->oldpwd)
	{
		free(data->oldpwd);
		data->oldpwd = NULL;
	}
	if (data && data->cmds)
		ft_free_cmds(data->cmds, data->cmds);
	reset_int(data);
//	free(data);
	data = NULL;
	rl_clear_history();
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

