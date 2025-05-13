/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by mavander          #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Converts an integer to a string.
// Allocates and returns a string representing the integer 'n'.
// Handles negative numbers and returns NULL if allocation fails.
char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	size_t	size;

	nbr = n;
	size = (nbr <= 0) ? 1 : 0;
	if (nbr < 0)
		nbr = -nbr;
	while (n)
	{
		n /= 10;
		size++;
	}
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size--] = '\0';
	if (nbr == 0)
		str[0] = '0';
	while (nbr)
	{
		str[size--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (size == 0 && str[1] != '\0')
		str[0] = '-';
	return (str);
}
