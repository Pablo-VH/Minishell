/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:48:18 by pavicent          #+#    #+#             */
/*   Updated: 2025/02/10 13:48:20 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "gertru.h"

int	do_echo(t_pipes *data, char **builtin)
{
	
}

int	check_builtin(t_pipes *data, int in_child)
{
	char	**args;

	args = ft_split(data->cmds->cmd, " ");
	if (!args || !args[0])
		return (1);
	else if (in_child == 1 && !ft_strcmp(args[0], "echo"))
		return (do_echo(data, args), 1);
	else if (in_child == 1 && !ft_strcmp(args[0], "pwd"))
		return (printf("%s\n", data->pwd));
	else if (in_child == 1 && !ft_strcmp(args[0], "env"))
		return (print_env(data), 1);
	else if (!ft_strcmp(args[0], "cd"))
		return (do_cd(data, args), 1);
	else if (!ft_strcmp(args[0], "export"))
		return (export(data), 1);
	else if (!ft_strcmp(args[0], "unset"))
	{
		g_exit_status = 0;
		return (unset(data), 1);
	}
	else if (!ft_strcmp(args[0], "exit"))
		return (do_exit(data, in_child));
	return (0);
}
