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

static t_bool	echo_flag(t_cmd *cmd)
{
	char	*arg_name;
	int		i;

	arg_name = ((t_arg *)cmd->arg->next->content)->name;
	i = 1;
	while (arg_name[i])
	{
		if (arg_name[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void	print_args(t_list	*arg_lst)
{
	while (arg_lst)
	{
		ft_putstr_fd(((t_arg *)arg_lst->content)->name, STDOUT_FILENO);
		if (arg_lst->next)
			ft_putchar_fd(' ', STDOUT_FILENO);
		arg_lst = arg_lst->next;
	}
}

int	ft_echo(t_shell *sh, t_list **env, t_cmd *cmd)
{
	t_list	*arg_lst;
	t_bool	flag;

	(void)env;
	(void)sh;
	arg_lst = cmd->arg->next;
	if (!arg_lst)
		return (ft_printfd(STDOUT_FILENO, "\n"), EXIT_SUCCESS);
	flag = FALSE;
	if (!ft_strncmp(((t_arg *)arg_lst->content)->name, "-n", 2))
	{
		if (echo_flag(cmd) == TRUE)
		{
			flag = TRUE;
			arg_lst = arg_lst->next;
		}
	}
	print_args(arg_lst);
	if (flag == FALSE)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
