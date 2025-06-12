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
#include <errno.h>

int	main(int ac, char **av, char **env)
{
	t_shell	*sh;

	sh = ft_calloc(sizeof(t_shell));
	ft_parser(sh);
	// ((t_cmd *)cmd->content)->redir = NULL;
	// ((t_cmd *)cmd->content)->arg = NULL;

	print_list(sh->cmd, CMD);
	(void)ac;
	(void)av;
	(void)env;
}
