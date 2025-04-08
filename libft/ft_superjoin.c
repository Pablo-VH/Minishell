/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:46:38 by dgargant          #+#    #+#             */
/*   Updated: 2025/01/23 12:59:38 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_superjoin(const char *s1, char c, const char *s2)
{
	char	*first;
	char	*second;
	char	*res;
	size_t	i;

	first = (char *)s1;
	second = (char *)s2;
	i = 0;
	if (first == NULL)
		return (second);
	else if (second == NULL)
		return (first);
	res = (char *) malloc((ft_strlen(first) + ft_strlen(second) + 2)
			* sizeof(char));
	if (res == NULL)
		return (NULL);
	while (*first != 0)
		res[i++] = *first++;
	if (c)
		res[i++] = c;
	while (*second != 0)
		res[i++] = *second++;
	res[i] = '\0';
	return (res);
}
