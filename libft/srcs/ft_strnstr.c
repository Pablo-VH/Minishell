/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:57:12 by dgargant          #+#    #+#             */
/*   Updated: 2024/02/20 10:41:06 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*aux;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			j++;
			if (needle[j] == '\0')
			{
				aux = (char *)&haystack[i];
				return (aux);
			}
		}
		i++;
	}
	return (0);
}

	/*
    #include <stdio.h>
    #include <string.h>
    
    int main()
{
    const char *haystack = "hola mundano do mundo";
    const char *needle = "mundo";
    size_t len = -1;

    char *result = strnstr(haystack, needle, len);

    if (result != NULL) {
        printf("La subcadena '%s' fue encontrada en la cadena '%s'
         dentro de los primeros %i caracteres.\n resultado: '%s'. ",
               needle, haystack, (int)len, result);
    } else {
        printf("La subcadena '%s' no fue encontrada en la cadena 
        '%s' dentro de los primeros %zu caracteres.\n",
               needle, haystack, len);
    }
    return (0);
}*/
