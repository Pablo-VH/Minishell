/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:41:54 by dgargant          #+#    #+#             */
/*   Updated: 2024/02/16 10:59:40 by dgargant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((ft_isalpha(c) || ft_isdigit(c)))
		return (1);
	return (0);
}

/*int main(void)
{
	char letter = '8';
	char al = ft_isalnum(letter);
	
	if(al)
		printf("\nel caracter es: %d\n", al);
	else
		printf("no es un caracter");
}*/
