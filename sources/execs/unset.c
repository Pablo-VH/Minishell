/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:21:38 by pavicent          #+#    #+#             */
/*   Updated: 2025/05/08 13:21:40 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

static char	**ft_delete_var(char **env, int pos)
{
	char	**new_env;
	int		size;
	int		i;

	size = ft_array_length(env);
	new_env = ft_calloc(size, sizeof(char *));
	i = 0;
	while (i != pos)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	while (env[i + 1])
	{
		new_env[i] = ft_strdup(env[i + 1]);
		i++;
	}
	ft_free_void_array((void **)env);
	return (new_env);
}

static void	unset_oldpwd_pwd(t_pipes *data, char *arg)
{
	if (!ft_strcmp(arg, "OLDPWD"))
	{
		free(data->oldpwd);
		data->oldpwd = NULL;
	}
	else if (!ft_strcmp(arg, "PWD"))
	{
		free(data->pwd);
		data->pwd = NULL;
	}
}

void	unset(t_pipes *data)
{
	int	i;
	int	j;
	int	n;

	if (!data->env)
		return ;
	i = 0;
	while (data->cmds->cmds[i])
	{
		j = 0;
		if (ft_strcmp(data->cmds->cmds[i], "unset"))
		{
			unset_oldpwd_pwd(data, data->cmds->cmds[i]);
			n = ft_lgth(data->env[j], data->cmds->cmds[i]);
			while (data->env[j]
				&& ft_strncmp(data->env[j], data->cmds->cmds[i], n))
			{
				j++;
				n = ft_lgth(data->env[j], data->cmds->cmds[i]);
			}
			if (data->env[j])
				data->env = ft_delete_var(data->env, j);
		}
		i++;
	}
}
