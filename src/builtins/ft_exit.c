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

int	ft_exit(t_shell *sh, t_list **env, t_cmd *cmd)
{
	t_list	*args;
	char	*arg_name;
	int		i;
	int		ret_nb;

	(void)env;
	i = 0;
	if (!cmd->arg->next)
		exit(atoi(sh->last_err));
	args = cmd->arg->next;
	if (args->next)
		return (ft_putstr_fd(FTERR_EXIT_ARG"\n", STDERR_FILENO), 1);
	arg_name = ((t_arg *)args->content)->name;
	ret_nb = atoi(arg_name);
	while (arg_name[i])
	{
		if (arg_name[i] == '+' || arg_name[i] == '-')
			i++;
		if (!isdigit(arg_name[i++]))
		{
			ft_printfd(STDERR_FILENO, FTERR_EXIT_NB, arg_name);
			exit(2);
		}
	}
	if (ret_nb < 0)
		ret_nb = 256 - (ret_nb * -1);
	exit(ft_abs(ret_nb) & 0xFF);
	return (0);
}
