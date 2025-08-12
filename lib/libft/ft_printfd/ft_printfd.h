/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:05:53 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:14:25 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTFD_H
# define FT_PRINTFD_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>

int		ft_pn_b(int fd, long long n, char *base);
int		ft_print_ptr(int fd, unsigned long long ptr);
int		ft_printchar(int fd, int c);
int		ft_printstr(int fd, char *str);
int		ft_printpct(int fd);
size_t	ft_strlen(const char *s);
void	ft_putstr(int fd, char *str);
int		ft_formats(int fd, va_list args, const char format);
int		ft_printfd(int fd, const char *format, ...);

#endif
