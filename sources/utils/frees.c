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

void	ft_free_lst(t_pipes *data)
{
	t_cmds	*next;
	int		i;

	while (data->cmds)
	{
		i = 0;
		next = data->cmds->next;
		ft_free_void_array((void **)data->cmds->cmds);
		while (data->cmds->s_files && data->cmds->s_files->file[i])
		{
			free(data->cmds->s_files->file[i]);
			i++;
		}
		if (data->cmds->s_files->flagfd)
		{
			free(data->cmds->s_files->file);
			free(data->cmds->s_files->fd);
			free(data->cmds->s_files->flagfd);
		}
		free(data->cmds->s_files);
		data->cmds->stop_exec = 0;
		free(data->cmds);
		data->cmds = NULL;
		data->cmds = next;
	}
}

void	free_cmdss(t_cmds *lst)
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
	ft_free_void_array((void **)data->env);
	ft_free_lst(data);
	if (data->pwd)
		free(data->pwd);
	if (data->oldpwd)
		free(data->oldpwd);
	rl_clear_history();
	ft_free_pids(&data->pids);
}

void	ft_free_tab(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_free_pids(pid_t **pids)
{
	if (*pids)
	{
		free(*pids);
		*pids = NULL;
	}
}
