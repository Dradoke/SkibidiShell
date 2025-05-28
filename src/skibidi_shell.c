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
	t_cmd	*content;

	cmd = (t_list *)ft_calloc(sizeof(t_list));

	cmd->content = ft_calloc(sizeof(t_cmd));

	((t_cmd *)cmd->content)->redir = ft_calloc(sizeof(t_list));
	((t_cmd *)cmd->content)->arg = ft_calloc(sizeof(t_list));

	((t_cmd *)cmd->content)->redir->content = ft_calloc(sizeof(t_redir));
	((t_cmd *)cmd->content)->arg->content = ft_calloc(sizeof(t_arg));

	((t_redir *)((t_cmd *)cmd->content)->redir->content)->name = ft_calloc(sizeof(char));
	((t_redir *)((t_cmd *)cmd->content)->redir->content)->name = ft_calloc(sizeof(char));
	ft_lstadd_back(cmd, ft_lstnew(content));


	((t_redir *)((t_cmd *)cmd->content)->redir->content)->type = OUTFILE;
}