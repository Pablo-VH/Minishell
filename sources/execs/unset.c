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

static char	**ft_delete_env_var(char **env, int i)
{
	int		len;
	char	**res;
	int		j;

	len = ft_array_length(env);
	res = ft_calloc(len, sizeof(char *));
	j = 0;
	while (env[j])
	{
		if (strncmp(env[j], env[i], ft_strlen(env[j])))
			res[j] = ft_strdup(env[j]);
		j++;
	}
	res[j] = NULL;
	ft_free_void_array((void **)env);
	return (res);
}

void	unset(t_pipes *data)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	if (!data->env)
		return ;
	while (data->cmds->cmds[i])
	{
		j = 0;
		while (data->env[j])
		{
			if (ft_strcmp(data->cmds->cmds[i], "unset"))
			{
				len = ft_strlen(data->cmds->cmds[i]);
				while (data->env[j]
					&& ft_strncmp(data->cmds->cmds[i], data->env[j], len))
					j++;
				if (data->env[j])
					data->env = ft_delete_env_var(data->env, j);
			}
		}
		i++;
	}
}
