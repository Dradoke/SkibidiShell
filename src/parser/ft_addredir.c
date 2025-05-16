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

t_redir_type get_redir_type(char *line, int *i)
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
			ft_error(FTERR_REDIR);
	}
	else if (line[*i] == '>')
	{
		(*i)++;
		if (line[*i] == '>')
			type == APPEND;
		else if (ft_isprint(line[*i]) && !ft_isdelim(line[*i]))
			type = OUTFILE;
		else
			ft_error(FTERR_REDIR);
	}
	(*i)++;
	return (type);
}
