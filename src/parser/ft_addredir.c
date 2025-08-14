/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addredir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:37 by mavander          #+#    #+#             */
/*   Updated: 2025/08/14 19:35:33 by mavander         ###   ########.fr       */
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
	return (NOT_REDIR);
}

static t_redir	*redircontent(t_shell *sh)
{
	t_redir	*tredir;

	tredir = ft_calloc(sizeof(t_redir));
	if (!tredir)
		return (ft_seterror(sh, FTERR_ALLOC, 2), NULL);
	tredir->type = get_redir_type(sh->line, &sh->i);
	tredir->name = ft_cpyword(sh);
	if (!tredir->name || tredir->type == NOT_REDIR)
		return (free(tredir), NULL);
	return (tredir);
}

t_bool	ft_addredir(t_shell *sh, t_cmd *tcmd)
{
	ft_lstadd_back(&tcmd->redir, ft_lstnew(redircontent(sh)));
	if (!ft_lstlast(tcmd->redir)->content)
		return (FALSE);
	return (TRUE);
}
