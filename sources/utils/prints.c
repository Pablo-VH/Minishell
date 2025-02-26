/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:55:47 by pavicent          #+#    #+#             */
/*   Updated: 2025/02/26 12:55:49 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

void	write_error(char *msg, char *arg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putendl_fd(arg, STDERR_FILENO);
}

void	print_env(t_pipes *data)
{
	int	i;

	i = 0;
	if (data->env)
	{
		while (data->env[i])
		{
			printf("%s\n", data->env[i]);
			i++;
		}
	}
}
