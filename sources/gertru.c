/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gertru.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:34:28 by dgargant          #+#    #+#             */
/*   Updated: 2025/05/18 23:11:02 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

unsigned char	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_pipes	data;

	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	ft_memset(&data, 0, sizeof(t_pipes));
	get_pwd(&data);
	data.env = ft_init_env(envp);
	if (argc == 1)
		read_input(&data);
	return (0);
}
