#include "gertru.h"

char	*ft_find_env_var(char *envp[], char *var, int len)
{
	int	i;

	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			if (ft_strncmp(envp[i], var, len) == 0)
				return (envp[i] + len);
			i++;
		}
	}
	return (NULL);
}

void	get_pwd(t_pipes *data)
{
	char	*tmp;

	if (data->pwd)
	{
		if (data->oldpwd)
			free(data->oldpwd);
		data->oldpwd = ft_strdup(data->pwd);
		free(data->pwd);
	}
	data->pwd = getcwd(NULL, 0);
	if (!data->oldpwd)
	{
		tmp = ft_find_env_var(data->env, "OLDPWD=", 7);
		data->oldpwd = ft_strdup(tmp);
		if (!data->oldpwd)
			data->oldpwd = ft_strdup(data->pwd);
	}
}