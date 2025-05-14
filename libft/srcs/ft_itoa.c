/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:28:53 by pavicent          #+#    #+#             */
/*   Updated: 2024/02/13 09:34:02 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		n = -n;
	if (n == 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		len;
	long	nbr;

	nbr = n;
	len = ft_numlen(nbr);
	if (nbr >= 0)
		num = (char *)malloc(sizeof(char) * len + 1);
	else
		num = (char *)malloc(sizeof(char) * len++ + 2);
	if (num == NULL)
		return (NULL);
	if (n < 0)
		nbr = -nbr;
	num[len] = '\0';
	while (len-- > 0)
	{
		num[len] = (char)(nbr % 10 + '0');
		nbr = nbr / 10;
	}
	if (n < 0)
		num[0] = '-';
	return (num);
}
