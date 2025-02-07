/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:24:17 by pavicent          #+#    #+#             */
/*   Updated: 2024/12/18 10:29:01 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

void	free_fd(t_pipes *data)
{
	int	i;

	i = 0;
	if (data->fd)
	{
		if (data->fd[i])
		{
			while (data->fd[i])
			{
				free(data->fd[i]);
				i++;
			}
		}
		free(data->fd);
		data->fd = NULL;
	}
}
