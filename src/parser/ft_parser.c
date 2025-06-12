/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

static void	set_last_redir(t_cmd *tcmd)
{
	t_list	*lredir;
	t_redir	*tredir;

	lredir = tcmd->redir;
	tredir = lredir->content;
	while (lredir->next)
	{
		if (tredir->type == INFILE
			|| tredir->type == HEREDOC)
			tcmd->last_redir[INPUT] = tredir;
		else if (tredir->type == OUTFILE
			|| tredir->type == APPEND)
			tcmd->last_redir[OUTPUT] = tredir;
		lredir = lredir->next;
	}
}

static void	new_command(t_shell *sh)
{
	ft_lstadd_back(&sh->cmd, ft_lstnew(ft_calloc(sizeof(t_cmd))));
	while (sh->line[sh->i] != '|')
	{
		while (ft_isspace(sh->line[sh->i]))
			sh->i++;
		if (ft_isdelim(sh->line[sh->i]))
			ft_newredir(sh, sh->cmd->content);
		sh++;
	}
	set_last_redir(sh->cmd->content);
	
}

t_list	*ft_parser(t_shell *sh)
{
	sh->cmd = ft_lstnew(ft_calloc(sizeof(t_cmd)));
	// if (!ft_lstlast(sh->cmd)->index)
	// 	manage_first_cmd();
	while (sh->line[sh->i])
	{
		ft_skipspace(sh->line, &sh->i);
		if (sh->line[sh->i] == '|')
		{
			sh->i++;
			if (!sh->cmd->index)
				perror("SkibidiShell: syntax error near unexpected token '|'");
			else
				new_command(sh);
		}
	}
	return (sh->cmd);
}
