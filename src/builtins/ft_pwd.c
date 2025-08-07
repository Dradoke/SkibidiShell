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

int	ft_pwd(t_shell *sh, t_list **env, t_cmd *cmd)
{
	char	*curr_path;

	(void)sh;
	(void)cmd;
	curr_path = ft_getenv_val(*env, "PWD");
	if (curr_path != NULL)
	{
		ft_putstr_fd(curr_path, 1);
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
