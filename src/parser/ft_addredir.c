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

static char	*get_redir_name(char *line, int *i)
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
	while (k < *i - j)
		name[k++] = line[j++];
	return (name);
}

void	ft_addredir(t_cmd *cmd, char *line, int *i)
{
	t_list	*new_redir;
	t_redir	*content;

	content = (t_redir *)ft_calloc(sizeof(t_redir));
	if (!content)
		return ;
	content->type = get_redir_type(line, i);
	content->name = get_redir_name(line, i);
	// content->name = ft_cpyword(line, i);
	new_redir = ft_lstnew(content);
	ft_lstadd_back(&cmd->redir, new_redir);
}
