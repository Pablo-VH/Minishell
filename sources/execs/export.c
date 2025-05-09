/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:06:49 by pavicent          #+#    #+#             */
/*   Updated: 2025/05/06 11:36:03 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

void	ft_change_var(t_pipes *data, int pos_env, int pos_arg)
{
	char	*tmp;

	tmp = data->env[pos_env];
	data->env[pos_env] = ft_strdup(data->cmds->cmds[pos_arg]);
	free(tmp);
}

char	**ft_new_var(t_pipes *data, int pos)
{
	char	**res;
	int		i;
	int		len;

	i = 0;
	len = ft_array_length(data->env);
	res = ft_calloc(len + 2, sizeof(char *));
	while (data->env[i])
	{
		res[i] = ft_strdup(data->env[i]);
		i++;
	}
	res[i] = ft_strdup(data->cmds->cmds[pos]);
	res[i + 1] = NULL;
	ft_free_void_array((void **)data->env);
	return (res);
}

void	export_2(t_pipes *data, int i)
{
	int		j;
	int		var;

	j = 0;
	var = 0;
	if (ft_strcmp(data->cmds->cmds[i], "export"))
	{
		while (data->env[j])
		{
			if (!strncmp(data->cmds->cmds[i], data->env[j],
					ft_strlen(data->env[j])))
				var = 1;
			j++;
		}
		if (var == 0)
			data->env = ft_new_var(data, i);
		else
			ft_change_var(data, j, i);
	}
}

void	export(t_pipes *data)
{
	int	i;

	i = 0;
	if (!data->env)
		return ;
	while (data->cmds->cmds[i])
	{
		export_2(data, i);
		i++;
	}
}
