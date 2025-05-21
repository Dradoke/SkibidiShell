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

static t_redir_type	get_redir_type(char *line, int *i)
{
	t_redir_type	type;

	if (line[*i] == '<')
	{
		(*i)++;
		if (line[*i] == '<')
			type = HEREDOC;
		else if (ft_isprint(line[*i]) && !ft_isdelim(line[*i]))
			type = INFILE;
		else
			return ((t_redir_type)NULL);
	}
	else if (line[*i] == '>')
	{
		(*i)++;
		if (line[*i] == '>')
			type = APPEND;
		else if (ft_isprint(line[*i]) && !ft_isdelim(line[*i]))
			type = OUTFILE;
		else
			return ((t_redir_type)NULL);
	}
	(*i)++;
	return (type);
}

bool	ft_addredir(t_cmd *cmd, char *line, int *i)
{
	t_list	*new_redir;
	t_redir	*content;

	content = (t_redir *)ft_calloc(sizeof(t_redir));
	if (!content)
		return (0);
	new_redir = ft_lstnew(content);
	ft_lstadd_back(cmd->redir, new_redir);
}
