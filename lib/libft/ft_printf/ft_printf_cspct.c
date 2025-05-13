/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cspct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilesi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:27 by jmilesi           #+#    #+#             */
/*   Updated: 2023/05/26 01:23:24 by jmilesi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Prints a single character to standard output.
// Writes character 'c' using the write system call.
// Returns 1 (number of characters printed).
int	ft_printchar(int c)
{
	write(1, &c, 1);
	return (1);
}

// Outputs a string to standard output.
// Writes each character in 'str' to stdout in sequence.
// Helper function with no return value.
void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

// Prints a string to standard output.
// Handles NULL strings by printing "(null)".
// Returns the number of characters printed.
int	ft_printstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

// Prints a percent sign to standard output.
// Handles the %% format specifier in ft_printf.
// Returns 1 (number of characters printed).
int	ft_printpct(void)
{
	write(1, "%", 1);
	return (1);
}
