/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:37:50 by pavicent          #+#    #+#             */
/*   Updated: 2025/05/27 12:37:52 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

void	put_exp(t_pipes *data, char *line, char *exp, int j)
{
	while (line[j])
	{
		if (j == data->pars->ei)
		{
			while (line[j] && !ft_isspace(line[j]) && !ft_is_token(line, j)
				&& line[j] != '|' && line[j] != '"' && line[j] != '\'')
				j++;
			if (exp)
			{
				while (exp[data->pars->l])
				{
					data->pars->new_line[data->pars->k] = exp[data->pars->l];
					data->pars->k++;
					data->pars->l++;
				}
			}
		}
		data->pars->new_line[data->pars->k] = line[j];
		if (line[j])
		{
			data->pars->k++;
			j++;
		}
	}
}

char	*insert_expansion(t_pipes *data, char *line, char *var, char *exp)
{
	int	j;

	j = 0;
	data->pars->k = 0;
	data->pars->l = 0;
	data->pars->new_len = 0;
	if (!line)
		return (NULL);
	data->pars->new_len = (ft_strlen(line) - (ft_strlen(var) + 1))
		+ ft_strlen(exp);
	data->pars->new_line = ft_calloc(data->pars->new_len + 1, sizeof(char));
	put_exp(data, line, exp, j);
	free(var);
	var = NULL;
	free(exp);
	exp = NULL;
	return (data->pars->new_line);
}

char	*search_in_env(t_pipes *data, char *v_search)
{
	int		i;
	char	*path;
	size_t	v_length;

	i = 0;
	v_length = ft_strlen(v_search);
	path = NULL;
	if (!v_search)
		return (NULL);
	if (data->env == NULL || v_search == NULL)
		return (NULL);
	if (!ft_strcmp(v_search, "?"))
		return (ft_itoa((int)g_exit_status));
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], v_search, v_length + 1))
		{
			path = ft_strdup(data->env[i] + v_length + 1);
			break ;
		}
		i++;
	}
	return (path);
}
