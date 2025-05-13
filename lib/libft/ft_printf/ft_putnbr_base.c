/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:45:36 by jmilesi           #+#    #+#             */
/*   Updated: 2025/03/19 15:54:34 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

// Prints a number in a specified base.
// Recursively converts and writes 'n' using the characters in 'base'.
// Returns number of characters printed.
int	ft_pn_b(long long n, char *base)
{
	uintmax_t	nbr;
	uintmax_t	base_length;
	int			len;

	len = 0;
	base_length = ft_strlen(base);
	if (n < 0)
	{
		len += write(1, "-", 1);
		nbr = -n;
	}
	else
		nbr = n;
	if (nbr >= base_length)
		len += ft_pn_b(nbr / base_length, base);
	len += write(1, &base[nbr % base_length], 1);
	return (len);
}

// Prints a pointer address in hexadecimal format.
// Handles NULL pointers by printing "(nil)" instead of an address.
// Returns number of characters printed.
int	ft_print_ptr(unsigned long long ptr)
{
	int			len;
	uintmax_t	nbr;
	uintmax_t	base_length;
	char		*base;

	if (ptr == 0)
		return (write(1, "(nil)", 5));
	len = write(1, "0x", 2);
	base = "0123456789abcdef";
	base_length = 16;
	nbr = ptr;
	if (nbr >= base_length)
		len += ft_pn_b(nbr / base_length, base);
	len += write(1, &base[nbr % base_length], 1);
	return (len);
}
