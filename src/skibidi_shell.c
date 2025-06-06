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
	t_list	*cmd;
	t_shell	*shell;

	shell = ft_calloc(sizeof(t_shell));
	shell->env = env;
	shell->cmd = cmd;
	shell->line = ft_strdup(av[1]);

	cmd = ft_lstnew(ft_calloc(sizeof(t_cmd)));
	ft_parser(shell);
	// ((t_cmd *)cmd->content)->redir = NULL;
	// ((t_cmd *)cmd->content)->arg = NULL;

	print_list(cmd, CMD);
	(void)ac;
	(void)av;
	(void)env;
}
