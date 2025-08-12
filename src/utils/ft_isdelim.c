/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdelim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:13:10 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:13:11 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

// Checks if a char is whether a < > |
//
// Return:
// 1 if it is
// 0 if not
t_bool	ft_isdelim(int c)
{
	if (c == '<' || c == '>' || c == '|')
		return (TRUE);
	return (FALSE);
}
