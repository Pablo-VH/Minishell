/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:34:29 by pavicent          #+#    #+#             */
/*   Updated: 2025/03/10 10:34:33 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(name)) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char	*cmd, char **env)
{
	int		i;
	char	*exect;
	char	**allpath;
	char	*part_p;

	i = -1;
	if (ft_getenv("PATH", env) == NULL && access(cmd, 0) == 0)
		return (cmd);
	if (ft_getenv("PATH", env) == NULL)
		return (NULL);
	allpath = ft_split(ft_getenv("PATH", env), ':');
	while (allpath[++i])
	{
		part_p = ft_strjoin(allpath[i], "/");
		exect = ft_strjoin(part_p, cmd);
		free(part_p);
		if (access(exect, F_OK | X_OK) == 0)
		{
			ft_free_void_array((void **)allpath);
			return (exect);
		}
		free(exect);
	}
	ft_free_void_array((void **)allpath);
	return (NULL);
}

void	executor(t_pipes *data, t_cmds *tmp)
{
	char	*path;

	if (check_builtin(data, 1))
	{
		ft_free_all(data);
		exit(EXIT_FAILURE);
	}
	if (data->cmds->args[0] == NULL)
		path = NULL;
	else if (data->cmds->args[0][0] != '.' && data->cmds->args[0][0] != '/')
		path = get_path(data->cmds->args[0], data->env);
	else
	{
		if (access(data->cmds->args[0], F_OK) == 0)
			path = data->cmds->args[0];
	}
	if (path != NULL && access(path, X_OK) == 0)
		execve(path, data->cmds->args, data->env);
	else
	{
		data->cmds = tmp;
		perror("minishell: command not found");
		ft_free_all(data);
		exit(EXIT_FAILURE);
	}
}
