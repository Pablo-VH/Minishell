/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:19:22 by pavicent          #+#    #+#             */
/*   Updated: 2025/05/08 13:19:25 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "gertru.h"

int	check_echo_flag(char *str, int *flag)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == '-')
			i++;
		else if (str[i] == 'n')
			i++;
		else
			return (1);
	}
	*flag = 1;
	return (0);
}

void	ft_echo(t_pipes *data, char **builtin)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	(void)data;
	while (builtin[i])
	{
		if (check_echo_flag(builtin[i], &flag))
			break ;
		i++;
	}
	while (builtin[i])
	{
		printf("%s", builtin[i]);
		if (builtin[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
}

int	check_builtin(t_pipes *data, int in_child)
{
	if (!data->cmds->cmds || !data->cmds->cmds[0])
		return (1);
	else if (in_child == 1 && !ft_strcmp(data->cmds->cmds[0], "echo"))
		return (ft_echo(data, data->cmds->cmds), 1);
	else if (in_child == 1 && !ft_strcmp(data->cmds->cmds[0], "pwd"))
	{
		if (!data->pwd)
			data->pwd = getcwd(NULL, 0);
		if (!data->pwd)
			return(printf("%s\n", data->oldpwd), 1);
		return (printf("%s\n", data->pwd), 1);
	}
	else if (in_child == 1 && !ft_strcmp(data->cmds->cmds[0], "env"))
		return (print_env(data), 1);
	else if (!ft_strcmp(data->cmds->cmds[0], "cd"))
		return (ft_cd(data, data->cmds->cmds), 1);
	else if (!ft_strcmp(data->cmds->cmds[0], "export"))
		return (export(data), 1);
	else if (!ft_strcmp(data->cmds->cmds[0], "unset"))
	{
		g_exit_status = 0;
		return (unset(data), 1);
	}
	else if (!ft_strcmp(data->cmds->cmds[0], "exit"))
		return (ft_exit(data, in_child, data->cmds->cmds));
	return (0);
}
