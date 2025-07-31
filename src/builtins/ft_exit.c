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

int ft_exit(t_shell *sh, t_list **env)
{
	t_list	*args;
	char	*arg_name;
	int i;

	(void)env;
	i = 0;
	if (!((t_cmd *)sh->cmd->content)->arg->next)
		exit(atoi(sh->last_err));
	args = ((t_cmd *)sh->cmd->content)->arg->next;
	arg_name = ((t_arg *)args->content)->name;
	while (arg_name[i])
	{
		if (!isdigit(arg_name[i++]))
		{
			// ft_printfd(STDERR_FILENO, FTERR_EXIT, arg_name);
			exit(255);
		}
	}
	exit(atoi(arg_name) & 0xFF);
	return (0);
}