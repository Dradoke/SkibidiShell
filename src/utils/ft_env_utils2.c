/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skibidi_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

t_bool	have_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	is_valid_key(char *str)
{
	if (ft_isalpha(str[0]) == FALSE && str[0] != '_')
		return (FALSE);
	return (TRUE);
}

t_bool	is_valid_env(char *str)
{
	if (!str)
		return (FALSE);
	if (is_valid_key(str) == FALSE)
		return (FALSE);
	if (have_equal(str) == FALSE)
		return (FALSE);
	return (TRUE);
}
