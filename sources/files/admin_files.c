/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:49:33 by pavicent          #+#    #+#             */
/*   Updated: 2025/02/10 13:49:35 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

static void	write_here_doc(t_pipes *data, char *limiter, int i, int lim_len)
{
	char	**line;

	line = ft_calloc(2, sizeof(char *));
	g_exit_status = 0;
	while (1)
	{
		line[0] = readline("> ");
		if (!line[0])
		{
			ft_putstr_fd("minishell: warning: here-document wanted ",
				STDERR_FILENO);
			ft_putstr_fd(limiter, STDERR_FILENO);
			break ;
		}
		line[0] = ft_strjoin_free(line[0], "\n");
		if (g_exit_status == 130)
			data->stop_exec_hd = 1;
		if (ft_strncmp(line[0], limiter, lim_len) == 0 || g_exit_status == 130)
			break ;
		if (data->cmds->s_files->exp[i])
			heredock_expansor(line, data);
		write(data->cmds->s_files->fd[i], line[0], ft_strlen(line[0]));
		free(line[0]);
	}
	return (ft_free_array((void **)line), free(limiter));
}

int	heredoc(t_pipes *data, int i)
{
	char	*limiter;

	limiter = ft_strjoin_free(data->cmds->s_files->file[i], "\n");
	open_tmp_file(data, i);
	write_here_doc(data, limiter, i, ft_strlen(limiter));
	close(data->cmds->s_files->file[i]);
	if (!data->stop_exec_hd)
		return (infile(data, i));
	else
		return (1);
}
