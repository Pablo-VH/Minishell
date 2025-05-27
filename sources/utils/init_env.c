/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:29:45 by pavicent          #+#    #+#             */
/*   Updated: 2025/04/07 13:29:48 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gertru.h"

char	**ft_init_env(char **str)
{
	int		len;
	int		i;
	char	**env;

	i = 0;
	len = ft_array_length(str);
	env = ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		env[i] = ft_strdup(str[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}
