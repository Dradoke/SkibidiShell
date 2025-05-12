/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:05:53 by jmilesi           #+#    #+#             */
/*   Updated: 2025/03/26 15:32:29 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Processes format specifiers and routes to appropriate printing functions.
// Handles c,s,p,d,i,u,x,X,% specifiers using corresponding functions.
// Returns number of characters printed.
int	ft_formats(va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_printchar(va_arg(args, int));
	else if (format == 's')
		len += ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		len += ft_print_ptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		len += ft_pn_b(va_arg(args, int), "0123456789");
	else if (format == 'u')
		len += ft_pn_b(va_arg(args, unsigned int), "0123456789");
	else if (format == 'x')
		len += ft_pn_b(va_arg(args, unsigned int), "0123456789abcdef");
	else if (format == 'X')
		len += ft_pn_b(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (format == '%')
		len += ft_printpct();
	return (len);
}

// Printf implementation with variadic arguments support.
// Parses format string, processes specifiers with ft_formats.
// Returns total number of characters printed.
int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;	

	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			len += ft_formats(args, format[i + 1]);
			i++;
		}
		else
		{
			len += write(1, &format[i], 1);
		}
		i++;
	}
	va_end(args);
	return (len);
}
