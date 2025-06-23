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
	while (lredir)
	{
		tredir = lredir->content;
		if (tredir->type == INFILE
			|| tredir->type == HEREDOC)
			tcmd->last_redir[INPUT] = tredir;
		else if (tredir->type == OUTFILE
			|| tredir->type == APPEND)
			tcmd->last_redir[OUTPUT] = tredir;
		lredir = lredir->next;
	}
}

static void	parse_command(t_shell *sh)
{
	ft_lstadd_back(&sh->cmd, ft_lstnew(ft_calloc(sizeof(t_cmd))));
	while (sh->line[sh->i] && sh->line[sh->i] != '|')
	{
		if (ft_isdelim(sh->line[sh->i]) && sh->line[sh->i] != '|')
			ft_addredir(sh, ft_lstlast(sh->cmd)->content);
		else if (ft_isprint(sh->line[sh->i]))
			ft_addarg(sh, ft_lstlast(sh->cmd)->content);
		ft_skipspace(sh->line, &sh->i);
	}
	if (((t_cmd *)ft_lstlast(sh->cmd)->content)->redir)
		set_last_redir(ft_lstlast(sh->cmd)->content);
}

t_list	*ft_parser(t_shell *sh)
{
	parse_command(sh);
	while (sh->line[sh->i])
	{
		ft_skipspace(sh->line, &sh->i);
		if (sh->line[sh->i] == '|')
		{
			sh->i++;
			ft_skipspace(sh->line, &sh->i);
			if (sh->line[sh->i] == '\0')
			{
				perror("SkibidiShell: syntax error near unexpected token '|'");
				return (NULL);
			}
			parse_command(sh);
		}
	}
	return (sh->cmd);
}
