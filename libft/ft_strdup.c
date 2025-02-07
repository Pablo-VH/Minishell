/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:54:36 by dgargant          #+#    #+#             */
/*   Updated: 2024/02/16 14:38:08 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str;
	char	*p;

	i = 0;
	str = (char *)s1;
	p = malloc(ft_strlen(str) + 1);
	if (p == 0)
		return (0);
	while (str[i] != '\0')
	{
		p[i] = str[i];
		++i;
	}
	p[i] = '\0';
	return (p);
}
