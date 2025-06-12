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
// DONE
static t_redir_type	get_redir_type(char *line, size_t *i)
{
	if (line[*i] == '<')
	{
		(*i)++;
		if (line[*i] == '<')
			return ((*i)++, HEREDOC);
		else if (ft_isprint(line[*i]) && !ft_isdelim(line[*i]))
			return ((*i)++, INFILE);
	}
	else if (line[*i] == '>')
	{
		(*i)++;
		if (line[*i] == '>')
			return ((*i)++, APPEND);
		else if (ft_isprint(line[*i]) && !ft_isdelim(line[*i]))
			return ((*i)++, OUTFILE);
	}
	(*i)++;
	return ((t_redir_type)NULL);
}
// NEED FIX
static char	*get_redir_name(char *line, size_t *i)
{
	char	*name;
	int		j;
	int		k;

	k = 0;
	while (ft_isspace(line[*i]))
		(*i)++;
	j = *i;
	while (!ft_isdelim(line[*i]) && !ft_isspace(line[*i]))
		(*i)++;
	name = ft_calloc(*i - j);
	while (k < (int)*i - j)
		name[k++] = line[j++];
	return (name);
}
// DONE
static t_redir	*redircontent(t_shell *sh)
{
	t_redir	*tredir;

	tredir = ft_calloc(sizeof(t_redir));
	tredir->type = get_redir_type(sh->line, &sh->i);
	tredir->name = get_redir_name(sh->line, &sh->i);
	return (tredir);
}
// UN-FINISHED
t_redir	*ft_newredir(t_shell *sh, t_cmd *tcmd)
{
	ft_lstadd_back(&tcmd->redir, ft_lstnew(redircontent(sh)));
	return((t_redir *)NULL);
}
