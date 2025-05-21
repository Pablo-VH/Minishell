/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 09:41:51 by dgargant          #+#    #+#             */
/*   Updated: 2024/02/23 09:18:28 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free2(const char *s1, const char *s2)
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
	res = (char *) malloc((ft_strlen(first) + ft_strlen(second) + 1)
			* sizeof(char));
	if (res == NULL)
		return (NULL);
	while (*first != 0)
		res[i++] = *first++;
	while (*second != 0)
		res[i++] = *second++;
	res[i] = '\0';
	free((char *)s1);
	free((char *)s2);
	return (res);
}

char	*ft_strjoin_free(const char *s1, const char *s2)
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
	res = (char *) malloc((ft_strlen(first) + ft_strlen(second) + 1)
			* sizeof(char));
	if (res == NULL)
		return (NULL);
	while (*first != 0)
		res[i++] = *first++;
	while (*second != 0)
		res[i++] = *second++;
	res[i] = '\0';
	free((char *)s1);
	return (res);
}

char	*ft_strjoin(const char *s1, const char *s2)
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
	res = (char *) malloc((ft_strlen(first) + ft_strlen(second) + 1)
			* sizeof(char));
	if (res == NULL)
		return (NULL);
	while (*first != 0)
		res[i++] = *first++;
	while (*second != 0)
		res[i++] = *second++;
	res[i] = '\0';
	return (res);
}
