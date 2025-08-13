/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:54 by mavander          #+#    #+#             */
/*   Updated: 2025/08/13 19:24:53 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

t_bool	is_valid_key(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (FALSE);
	while (str[i] && str[i] != '=')
		if (!ft_isalnum(str[i++]) && str[0] != '_')
			return (FALSE);
	return (TRUE);
}
