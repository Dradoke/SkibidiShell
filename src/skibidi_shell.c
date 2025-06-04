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

int	main(int ac, char **av, char **env)
{
	t_list	*cmd;

	cmd = ft_lstnew(NULL);
	ft_lstadd_back(&cmd, ft_lstnew(NULL));
	ft_lstadd_back(&cmd, ft_lstnew(NULL));
	ft_lstadd_back(&cmd, ft_lstnew(NULL));
	ft_lstadd_back(&cmd, ft_lstnew(NULL));

	print_list(cmd, CMD);
	(void)ac;
	(void)av;
	(void)env;
}
