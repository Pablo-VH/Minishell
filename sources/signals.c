/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:46:24 by pavicent          #+#    #+#             */
/*   Updated: 2025/05/19 13:46:26 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

void	handler(int signal)
{
	unsigned char	c_signal;

	c_signal = 130;
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		g_exit_status = g_exit_status & 0;
		g_exit_status = g_exit_status | c_signal;
	}
}
