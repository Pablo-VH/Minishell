/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:39:05 by dgargant          #+#    #+#             */
/*   Updated: 2025/05/18 23:46:08 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

char	*expand_init(t_pipes *data, char *line)
{
	char	*new_line;
	char	*var;
	char	*exp;
	int		i;

	i = 0;
	new_line = NULL;
	var = NULL;
	exp = NULL;
	
	//reccorrer la string buscando el '$' teniendo en cuenta las comillas
    while (line[i])
    {
		if ((line[i] == '"' && data->pars->fdb == 0) && data->pars->fs != 1)
			data->pars->fdb = 1;
		else if ((line [i] == '"' && data->pars->fdb == 1)
			&& data->pars->fs != 1)
			data->pars->fdb = 0;
		if ((line[i] == '\'' && data->pars->fs == 0) && data->pars->fdb != 1)
			data->pars->fs = 1;
		else if ((line [i] == '\'' && data->pars->fs == 1)
			&& data->pars->fdb != 1)
			data->pars->fs = 0;
		if (line[i] == '<' && line[i + 1] == '<')
		{
			// crear funcion para ignorar delimitador
			i += 2;
			while (!(line[i] >= '!' && line[i] <= 126))
				i++;
			while(line[i])
			{
			 	if (line[i] == '<' || line[i] == '>' || line[i] == '|')
					break;
				if (!(line[i] >= '!' && line[i] <= 126))
					break;
				i++;
			}
		}
		// si estoy en comillas simples ignoro la variable	
		//if (line[i] == '$' && (data->pars->fs == 1))
		//{
		//	while (line[i] && line[i] >= '!' && line[i] <= 126)
		//		i++;
		//	//data->pars->fs = 0;
		//}else 
		if (line[i] == '$' && (data->pars->fs == 0))
		{
			var = take_v(line, i);
			//printf("variable sin expandir: %s\n", var);
			exp = search_in_env(data, var);
			//printf("variable expandida: %s\n", exp);
			new_line = insert_expansion(line, var, exp, i);
			//printf("Nueva linea: %s\n", new_line);
			free(line);
			line = NULL;
			line = new_line;
		}
		if (line[i])
			i++;
	}
	return (line);
}

char	*take_v(char *line, int i)
{
	int 	j;
	char 	*new_v;

	j = 0;
	new_v = NULL;
	if (!line[i + 1] || ft_isspace(line[i + 1]))
		return (NULL);
	else
	{
		i++;
		j = i;
		while (line[j] && !ft_isspace(line[j]) && !ft_is_token(line, j)
			&& line[j] != '|' && line[j] != '"' && line[j] != '\'')
			j++;
		new_v = ft_substr(line, i , (j - i));
	}
	return (new_v);
}

char	*search_in_env(t_pipes *data, char *v_search)
{
	int		i;
	char	*path;
	size_t	v_length;

	i = 0;
	if (data->env == NULL || v_search == NULL)
		return (NULL);
	if (!ft_strcmp(v_search, "?"))
	{
		//i = g_exit_status | i;
		return (ft_itoa((int)g_exit_status));
	}
	path = NULL;
	v_length = ft_strlen(v_search);
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], v_search , v_length + 1))
		{
			path = ft_strdup(data->env[i] + v_length + 1);
			break ;
		}
		i++;
	}
	return (path);
}

char	*insert_expansion(char *line, char * var, char *exp, int i)
{
	int		j;
	int		k;
	int		l;
	size_t	new_legth;
	char	*new_line;

	j = 0;
	k = 0;
	l = 0;
	new_legth = 0;
	if (!line)
		return (NULL);
	new_legth = (ft_strlen(line) - (ft_strlen(var) + 1)) + ft_strlen(exp);
	//printf("<<<<< l: %zu, v: %zu, e: %zu, total: %zu >>>>>>> \n", ft_strlen(line), (ft_strlen(var) + 1),
	//	ft_strlen(exp), new_legth);
	new_line = ft_calloc(new_legth + 1, sizeof(char));
	while (line[j])
	{
		if (j == i)
		{
			while (line[j] && !ft_isspace(line[j]) && !ft_is_token(line, j)
			&& line[j] != '|' && line[j] != '"' && line[j] != '\'')
			{
				j++;
			}
			if (exp)
			{
				while (exp[l])
				{
					new_line[k] = exp[l];
					k++;
					l++;
				}
			}
		}
		new_line[k] = line[j];
		if (line[j])
		{
			k++;
			j++;
		}
	}
	free(var);
	var = NULL;
	free(exp);
	exp = NULL;
	return (new_line);
}

