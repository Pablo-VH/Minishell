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

int		check_echo_flag(char *str, int *flag)
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

void	ft_cd(t_pipes *data, char **builtin)
{
	if (array_length(builtin) > 2)
		write_n_status("minishell: cd: Too many arguments", 1);
	
}

int	check_builtin(t_pipes *data, int in_child)
{
	char	**args;

	args = ft_split(data->cmds->cmd, " ");
	if (!args || !args[0])
		return (1);
	else if (in_child == 1 && !ft_strcmp(args[0], "echo"))
		return (ft_echo(data, args), 1);
	else if (in_child == 1 && !ft_strcmp(args[0], "pwd"))
		return (printf("%s\n", data->pwd));
	else if (in_child == 1 && !ft_strcmp(args[0], "env"))
		return (print_env(data), 1);
	else if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(data, args), 1);
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
