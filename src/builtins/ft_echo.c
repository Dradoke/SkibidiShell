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

int ft_echo(t_list *args, t_list **env)
{
	t_list *arg_lst;

	(void)env;
	arg_lst = args->next;
	if (!((t_arg *)args->next->content)->name)
		return (0);
	while (arg_lst)
	{
		ft_putstr_fd(((t_arg *)arg_lst->content)->name, STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		arg_lst = arg_lst->next;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}