/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:56:40 by jmilesi           #+#    #+#             */
/*   Updated: 2025/03/06 13:53:41 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>

int		ft_pn_b(long long n, char *base);
int		ft_print_ptr(unsigned long long ptr);
int		ft_printchar(int c);
int		ft_printstr(char *str);
int		ft_printpct(void);
size_t	ft_strlen(const char *s);
void	ft_putstr(char *str);
int		ft_formats(va_list args, const char format);
int		ft_printf(const char *format, ...);

#endif
