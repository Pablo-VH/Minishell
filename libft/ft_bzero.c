/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:42:09 by dgargant          #+#    #+#             */
/*   Updated: 2024/02/19 12:08:41 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/*int main(void)
{
    char str[50] = "hola mundo, como estas";

    printf("\nantes de bzero: %s\n", str);

    //bzero(str + 3, 0 * sizeof(char));
    ft_bzero(str + 3, 0);

    printf("despues de bzero: %s\n", str);
    
    return (0);
}*/