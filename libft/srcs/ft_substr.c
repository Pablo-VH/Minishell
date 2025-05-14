/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:44:15 by dgargant          #+#    #+#             */
/*   Updated: 2024/02/19 16:10:38 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	char	*p;

	i = 0;
	str = (char *)s;
	if (!str || start > ft_strlen(str))
	{
		p = (char *) ft_calloc(1, sizeof(char));
		if (p == NULL)
			return (NULL);
		return (p);
	}
	if (len > (ft_strlen(str) - start))
		len = ft_strlen(str) - start;
	p = (char *) ft_calloc((len + 1), sizeof(char));
	if (p == 0)
		return (0);
	str += start;
	while (*str && (i < len))
		p[i++] = *str++;
	return (p);
}
/*
int main() {
   const char *s = "Hello, World!";
   unsigned int start = 7;
   size_t len = 18446744073709551615;
   char *result = ft_substr(s, start, len);
   printf("%s\n", result);
   free(result);
   return 0;
}*/
