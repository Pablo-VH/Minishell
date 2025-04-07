/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:54:09 by pavicent          #+#    #+#             */
/*   Updated: 2025/02/26 12:54:11 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

char	**ft_delete_env_var(char **env, int i)
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
	while (data->cmds->args[i])
	{
		j = 0;
		while (data->env[j])
		{
			if (ft_strcmp(data->cmds->args[i], "unset"))
			{
				len = ft_strlen(data->cmds->args[i]);
				while (data->env[j]
					&& ft_strncmp(data->cmds->args[i], data->env[j], len))
					j++;
				if (data->env[j])
					data->env = ft_delete_env_var(data->env, j);
			}
		}
		i++;
	}
}
