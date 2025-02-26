/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:44:43 by pavicent          #+#    #+#             */
/*   Updated: 2025/02/24 12:44:46 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

static int	check_args(char **builtin)
{
	int	i;

	i = 0;
	while (builtin[i])
	{
		if (i == 1)
		{
			if (ft_atoll(builtin[i]) == 1 && ft_atoi(builtin[i]) == 0)
			{
				write_error("minishell: exit: numeric argument required: ",
					builtin[i]);
				return (2);
			}
		}
		else if (i > 1)
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_exit(t_pipes *data, int in_child, char **builtin)
{
	int	exit_status;

	if (!in_child)
		printf("exit\n");
	/*if (data->file_fd != -1)
		close(data->file_fd);*/
	exit_status = check_args(builtin);
	if (!exit_status && builtin[1])
		exit_status = ft_atoi(builtin[1]);
	else if (exit_status == 0)
		exit_status = g_exit_status;
	else if (exit_status == 1)
	{
		g_exit_status = exit_status;
		return (1);
	}
	ft_free_all(data);
	exit(exit_status);
}
