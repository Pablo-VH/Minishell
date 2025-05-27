/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:40:29 by pavicent          #+#    #+#             */
/*   Updated: 2025/03/08 12:40:31 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

static int	init_pfd(t_pipes *data)
{
	int	i;

	i = 0;
	data->fd = ft_calloc(data->num_cmds, sizeof(int *));
	if (data->fd == NULL)
	{
		perror("malloc pfd");
		return (1);
	}
	while (i < data->num_cmds - 1)
	{
		data->fd[i] = ft_calloc(2, sizeof(int));
		if (data->fd[i] == NULL || (pipe(data->fd[i]) == -1))
		{
			perror("malloc pfd or pipe");
			if (data->pids)
				free(data->pids);
			ft_free_void_array((void **)data->fd);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_pids_n_pipes(t_pipes *data)
{
	data->pids = malloc(sizeof(pid_t) * data->num_cmds);
	if (!data->pids)
	{
		perror("malloc pids");
		return (1);
	}
	if (init_pfd(data))
		return (1);
	return (0);
}

static int	do_fork(t_pipes *data, int i)
{
	data->pids[i] = fork();
	if (data->pids[i] == -1)
	{
		if (data->pids)
			free(data->pids);
		perror("fork");
		close_pipes(data, data->num_cmds);
		return (1);
	}
	return (0);
}

static int	child_process(t_pipes *data, int i, t_cmds *tmp)
{
	if (do_fork(data, i))
		return (1);
	if (data->pids[i] == 0)
	{
		rl_clear_history();
		signal(SIGQUIT, SIG_DFL);
		pipes_redirs(data, i, tmp);
		if (!data->cmds->stop_exec)
			redir_files(data, tmp);
		close_files(tmp);
		if (data->cmds->stop_exec)
		{
			ft_free_struct2(data);
			exit(1);
		}
		executor(data, tmp);
	}
	return (0);
}

void	cmds_exec(t_pipes *data)
{
	int		i;
	t_cmds	*tmp;

	i = 0;
	tmp = data->cmds;
	if (init_pids_n_pipes(data))
		return ;
	while (i < data->num_cmds)
	{
		if (child_process(data, i, tmp))
			break ;
		signal(SIGINT, SIG_IGN);
		data->cmds = data->cmds->next;
		i++;
	}
	data->cmds = tmp;
	close_pipes(data, 0);
	close_files(data->cmds);
	wait_pids(data, 0);
	ft_free_pids(&data->pids);
}

/*void	pre_exp_dol(t_pipes *data, char *line, int *i)
{
	if ((line[*i] == '"' && data->pars->fdb == 0) && data->pars->fs != 1)
		data->pars->fdb = 1;
	else if ((line [data->pars->ei] == '"' && data->pars->fdb == 1)
		&& data->pars->fs != 1)
		data->pars->fdb = 0;
	if ((line[*i] == '\'' && data->pars->fs == 0) && data->pars->fdb != 1)
		data->pars->fs = 1;
	else if ((line[*i] == '\'' && data->pars->fs == 1) && data->pars->fdb != 1)
		data->pars->fs = 0;
	if (line[*i] == '<' && line[(*i) + 1] == '<')
	{
		(*i) += 2;
		while (!(line[*i] >= '!' && line[*i] <= 126))
			data->pars->ei++;
		while(line[*i])
		{
		 	if (line[*i] == '<' || line[*i] == '>' || line[*i] == '|')
				break;
			if (!(line[*i] >= '!' && line[*i] <= 126))
				break;
			(*i) += 1;
		}
	}
	if (line[*i] == '$' && (ft_isspace(line[(*i) + 1]) || !line[(*i) + 1]))
		(*i) += 1;
	if (line[*i] == '$' && (line[(*i) + 1] == '"' || ft_isspace(line[(*i) + 1])) 
		&& line[(*i) + 1] && (data->pars->fdb == 1))
		(*i) += 1;
}

char	*expand_init(t_pipes *data, char *line)
{
	char	*new_line;
	char	*var;
	char	*exp;

	data->pars->ei = 0;
	new_line = NULL;
	var = NULL;
	exp = NULL;
	data->pars->p_exp = -1;
    while (line[data->pars->ei])
    {
		pre_exp_dol(data, line, &data->pars->ei);
		if (line[data->pars->ei] == '$' && (data->pars->fs == 0))
		{
			var = take_v(data, line, data->pars->ei);
			exp = search_in_env(data, var);
			new_line = insert_expansion(data, line, var, exp);
			free(line);
			line = NULL;
			line = new_line;
		}
		if (line[data->pars->ei])
			data->pars->ei++;
		if (data->pars->p_exp > -1)
		{
			data->pars->ei = data->pars->p_exp;
			data->pars->p_exp = -1;
		}
	}
	return (line);
}

char	*take_v( t_pipes *data, char *line, int i)
{
	int		j;
	char	*new_v;

	j = 0;
	new_v = NULL;
	if (!line[i + 1] || ft_isspace(line[i + 1]))
	{
		j = i + 1;
		new_v = ft_substr(line, i, 2);
	}
	else if (line[i + 1] && (line[i + 1] == '"' || line[i + 1] == '\''))
	{
		data->pars->p_exp = i;
		return (NULL);
	}
	else
	{
		i++;
		j = i;
		while (line[j] && !ft_isspace(line[j]) && !ft_is_token(line, j)
			&& line[j] != '|' && line[j] != '"' && line[j] != '\'')
			j++;
		new_v = ft_substr(line, i, (j - i));
	}
	return (new_v);
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
*/