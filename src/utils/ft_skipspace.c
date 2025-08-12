/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skipspace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:13:19 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:13:20 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

t_bool	ft_skipspace(char *str, size_t *i)
{
	while (ft_isspace(str[*i]))
		(*i)++;
	return (TRUE);
}
