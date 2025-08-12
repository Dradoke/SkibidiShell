/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_critical.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:31 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:12:32 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

t_bool	is_critical(t_list *args)
{
	char		*cmd_name;
	int			i;
	static char	*critical_name[] = {"export", "unset", "cd", "exit"};

	if (!args)
		return (FALSE);
	cmd_name = ((t_arg *)args->content)->name;
	i = 0;
	while (i < 4)
	{
		if (ft_strcmp(cmd_name, critical_name[i]) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
