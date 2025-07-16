/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addredir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

static t_redir_type	get_redir_type(char *line, size_t *i)
{
	if (line[*i] == '<')
	{
		(*i)++;
		if (line[*i] == '<')
			return ((*i)++, HEREDOC);
		else if (ft_isprint(line[*i]) && !ft_isdelim(line[*i]))
			return (INFILE);
	}
	else if (line[*i] == '>')
	{
		(*i)++;
		if (line[*i] == '>')
			return ((*i)++, APPEND);
		else if (ft_isprint(line[*i]) && !ft_isdelim(line[*i]))
			return (OUTFILE);
	}
	return ((t_redir_type) NULL);
}

static t_redir	*redircontent(t_shell *sh)
{
	t_redir	*tredir;

	tredir = ft_calloc(sizeof(t_redir));
	if (!tredir)
		return (ft_seterror(sh, FTERR_ALLOC, 2), NULL);
	tredir->type = get_redir_type(sh->line, &sh->i);
	tredir->name = ft_cpyword(sh);
	if (!tredir->name)
		return (NULL);
	return (tredir);
}

bool	ft_addredir(t_shell *sh, t_cmd *tcmd)
{
	ft_lstadd_back(&tcmd->redir, ft_lstnew(redircontent(sh)));
	if (!ft_lstlast(tcmd->redir)->content)
		return (false);
	return (true);
}
