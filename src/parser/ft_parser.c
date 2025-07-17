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

static bool	parse_command(t_shell *sh)
{
	t_cmd	*newcmd;

	ft_skipspace(sh->line, &sh->i);
	if (!sh->line[sh->i])
		return (ft_seterror(sh, FTERR_SYNTAX, 2), false);
	if (sh->line[sh->i] == '|')
		return (ft_seterror(sh, FTERR_SYNTAX, 2), false);
	ft_lstadd_back(&sh->cmd, ft_lstnew(ft_calloc(sizeof(t_cmd))));
	newcmd = ft_lstlast(sh->cmd)->content;
	while (sh->line[sh->i] && sh->line[sh->i] != '|')
	{
		if (ft_skipspace(sh->line, &sh->i) && sh->line[sh->i] == '|')
			break ;
		if (ft_isdelim(sh->line[sh->i])
			&& !ft_addredir(sh, newcmd))
			return (false);
		else if (!ft_isspace(sh->line[sh->i]) && ft_isprint(sh->line[sh->i])
			&& !ft_addarg(sh, newcmd))
			return (false);
	}
	if (!newcmd->arg)
		return (ft_seterror(sh, FTERR_SYNTAX, 2), false);
	if (newcmd->redir)
		set_last_redir(newcmd);
	return (true);
}

bool	ft_parser(t_shell *sh)
{
	ft_skipspace(sh->line, &sh->i);
	if (!sh->line[sh->i])
		return (false);
	while (sh->line[sh->i])
	{
		if (!parse_command(sh))
			return (false);
		if (sh->line[sh->i] == '|')
		{
			sh->i++;
			if (!sh->line[sh->i])
				return (ft_seterror(sh, FTERR_SYNTAX, 2), false);
		}
	}
	return (true);
}
