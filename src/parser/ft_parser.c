/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:46 by mavander          #+#    #+#             */
/*   Updated: 2025/08/13 20:47:16 by mavander         ###   ########.fr       */
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

static t_bool	parse_command_loop(t_shell *sh, t_cmd *newcmd)
{
	while (sh->line[sh->i] && sh->line[sh->i] != '|')
	{
		if (ft_skipspace(sh->line, &sh->i) && sh->line[sh->i] == '|')
			break ;
		if (ft_isdelim(sh->line[sh->i]))
		{
			if (!ft_addredir(sh, newcmd))
				return (FALSE);
		}
		else if (!ft_isspace(sh->line[sh->i]) && ft_isprint(sh->line[sh->i]))
		{
			if (!ft_addarg(sh, newcmd))
				return (FALSE);
		}
		else if (sh->line[sh->i])
			sh->i++;
	}
	return (TRUE);
}

static t_bool	parse_command(t_shell *sh)
{
	t_cmd	*newcmd;

	ft_skipspace(sh->line, &sh->i);
	if (!sh->line[sh->i])
		return (ft_seterror(sh, FTERR_SYNTAX, 2), FALSE);
	if (sh->line[sh->i] == '|')
		return (ft_seterror(sh, FTERR_SYNTAX, 2), FALSE);
	ft_lstadd_back(&sh->cmd, ft_lstnew(ft_calloc(sizeof(t_cmd))));
	newcmd = ft_lstlast(sh->cmd)->content;
	if (!parse_command_loop(sh, newcmd))
		return (FALSE);
	if (newcmd->redir)
		set_last_redir(newcmd);
	return (TRUE);
}

t_bool	ft_parser(t_shell *sh)
{
	ft_skipspace(sh->line, &sh->i);
	if (!sh->line[sh->i])
		return (FALSE);
	while (sh->line[sh->i])
	{
		if (!parse_command(sh))
			return (FALSE);
		if (sh->line[sh->i] == '|')
		{
			sh->i++;
			if (!sh->line[sh->i])
				return (ft_seterror(sh, FTERR_SYNTAX, 2), FALSE);
		}
	}
	return (TRUE);
}
