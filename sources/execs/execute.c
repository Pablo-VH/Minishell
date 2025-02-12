/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:57:13 by pavicent          #+#    #+#             */
/*   Updated: 2025/02/10 12:57:15 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "gertru.h"

void	execute(t_pipes *data)
{
	int	stop;

	stop = open_heredocs(data);
	if (!stop)
		open_files(data);
	if (data->num_cmds == 1)
	{
		if (check_builtin(data, 0) == 1)
			return ;
	}
	cmds_exec(data);
	delete_hd(data);
}
