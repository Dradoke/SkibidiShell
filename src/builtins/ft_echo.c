/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:11:54 by mavander          #+#    #+#             */
/*   Updated: 2025/08/13 19:33:04 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

static t_bool	echo_flag(char *arg_name)
{
	int		i;

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
		ft_printfd(STDOUT_FILENO, ((t_arg *)arg_lst->content)->name);
		if (arg_lst->next)
			ft_printfd(STDOUT_FILENO, " ");
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
		while (echo_flag(((t_arg *)arg_lst->content)->name) == TRUE)
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
