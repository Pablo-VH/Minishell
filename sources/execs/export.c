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

int	set_quotes(char c, int *d_quote, int *s_quote)
{
	if (c == '\'' && !*s_quote && !*d_quote)
		*s_quote = 1;
	else if (c == '\'' && *s_quote)
		*s_quote = 0;
	if (c == '"' && !*d_quote && !*s_quote)
		*d_quote = 1;
	else if (c == '"' && *d_quote)
		*d_quote = 0;
	if (*s_quote || *d_quote)
		return (1);
	else
		return (0);
}

void	ft_change_var(t_pipes *data, int pos_env, int pos_arg)
{
	char	*tmp;

	tmp = data->env[pos_env];
	data->env[pos_env] = ft_strdup(data->cmds->cmds[pos_arg]);
	free(tmp);
}

int	check_export(char *export)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while ((export[i] && (export[i] != '=' || i == 0)) || !ft_strlen(export))
	{
		set_quotes(export[i], &d_quote, &s_quote);
		if ((i == 0 && !ft_isalpha(export[i]))
			|| (i != 0 && !ft_isalnum(export[i])) || !ft_strlen(export))
		{
			printf("export: %s not a valid identifier\n", export);
			g_exit_status = 1;
			return (0);
		}
		i++;
	}
	g_exit_status = 0;
	return (1);
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

/*void	export_2(t_pipes *data, int i)
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
}*/

void	export(t_pipes *data)
{
	int	size;
	int	i;
	int	j;

	i = -1;
	size = ft_array_length(data->env);
	/*if (ft_array_length(data->cmds->cmds) == 1)
		print_export(data->env);/////////////////////////////////////////////*/
	while (data->cmds->cmds[++i])
	{
		j = 0;
		if (ft_strcmp(data->cmds->cmds[i], "export")
			&& check_export(data->cmds->cmds[i])
			&& ft_strchr(data->cmds->cmds[i], '='))
		{
			while (data->env && data->env[j]
				&& ft_strncmp(data->env[j], data->cmds->cmds[i],
					ft_lgth(data->env[j], data->cmds->cmds[i])))
				j++;
			if (data->env && data->env[j])
				ft_change_var(data, j, i);
			else
				data->env = ft_new_var(data, i);
		}
	}
}
/*
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
*/