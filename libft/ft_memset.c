/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:50:19 by dgargant          #+#    #+#             */
/*   Updated: 2024/02/16 12:56:43 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = b;
	while (len-- > 0)
		*p++ = (unsigned char)c;
	return (b);
}

/*int main(void)
{
    char str[50] = "hola mundo";

    printf("antes de memset: %s\n", str);

    ft_memset(str + 3, '8', 2*sizeof(char));
    memset(str + 3, '.', 2*sizeof(char));
    printf("despues de memset: %s\n", str);

    return (0);
}*/