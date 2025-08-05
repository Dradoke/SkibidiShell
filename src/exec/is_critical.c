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

t_bool	is_critical(t_list *args)
{
	char		*cmd_name;
	int			i;
	static char	*critical_name[] = {"export", "unset", "cd", "exit"};

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
