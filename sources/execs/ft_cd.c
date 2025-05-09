/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:44:34 by pavicent          #+#    #+#             */
/*   Updated: 2025/02/24 12:44:37 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

static void	update_in_env(t_pipes *data, int j, int k)
{
	char	*cwd;

	if (j >= 0 && k >= 0 && data->env[k])
	{
		free(data->env[k]);
		data->env[k] = ft_strjoin("OLDPWD=", data->env[j] + 4);
	}
	if (j >= 0 && k >= 0 && data->env[j])
	{
		free(data->env[j]);
		cwd = getcwd(NULL, 0);
		data->env[j] = ft_strjoin("PWD=", cwd);
		free(cwd);
		if (!data->env[j])
			data->env[j] = ft_strjoin("PWD=", data->env[k] + 7);
	}
}

static void	update_pwd_n_oldpwd(t_pipes *data, char *pwd, char *oldpwd)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = -1;
	k = -1;
	if (data->env)
	{
		while (data->env[i])
		{
			if (ft_strncmp(data->env[i], pwd, ft_strlen(pwd)) == 0)
				j = i;
			if (ft_strncmp(data->env[i], oldpwd, ft_strlen(oldpwd)) == 0)
				k = i;
			i++;
		}
		update_in_env(data, j, k);
	}
	get_pwd(data);
}

static int	return_home(void)
{
	char	*home;
	int		res;

	home = getenv("HOME");
	if (home)
		res = chdir(home);
	else
	{
		printf("minishell: cd: HOME not set\n");
		g_exit_status = 1;
		res = -2;
	}
	return (res);
}

void	ft_cd(t_pipes *data, char **builtin)
{
	int	res;

	res = 0;
	if (ft_array_length(builtin) > 2)
		write_n_change_status("minishell: cd: Too many arguments", 1);
	if (builtin[1] && (builtin[1][0] != '~' && builtin[1][0] != '-'))
		res = chdir(builtin[1]);
	else if ((builtin[1] && builtin[1][0] == '~') || !builtin[1])
		res = return_home();
	else if (builtin[1] && builtin[1][0] == '-')
	{
		if (data->oldpwd)
			res = chdir(data->oldpwd);
		else
			write_n_change_status("minishell: cd: OLDPWD not set\n", 1);
	}
	if (res == -1)
		perror("cd");
	else
		update_pwd_n_oldpwd(data, "PWD", "OLDPWD");
	if (res != -2)
		g_exit_status = 0;
}
