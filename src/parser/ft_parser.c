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

static void	new_redir(char *line, char **env, int *i, t_cmd *redir)
{
	
}

static void	set_last_redir(t_cmd *content)
{
	while (content->redir->next)
	{
		if (((t_redir *)content->redir->content)->type == INFILE
			|| ((t_redir *)content->redir->content)->type == HEREDOC)
			content->last_redir[INPUT] = content->redir->content;
		else if (((t_redir *)content->redir->content)->type == OUTFILE
			|| ((t_redir *)content->redir->content)->type == APPEND)
			content->last_redir[OUTPUT] = content->redir->content;
	}
}

static void	new_command(char *line, char **env, int *i, t_list *cmd)
{
	ft_lstadd_back(&cmd, ft_lstnew(ft_calloc(sizeof(t_cmd))));
	while (line[*i] != '|')
	{
		while (isspace(line[*i]))
			(*i)++;
		if (ft_isdelim(line[*i]))
			new_redir(line, env, i, (t_cmd *)cmd->content);
		(*i)++;
	}
	set_last_redir(cmd->content);
	
}

t_list	*ft_parser(char *line, char **env)
{
	static size_t	i;
	static size_t	j;
	t_list			*cmd;
	
	cmd = ft_lstnew(ft_calloc(sizeof(t_cmd)));
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '|')
		{
			i++;
			if (!ft_lstlast(cmd)->prev)
				perror("SkibidiShell: syntax error near unexpected token '|'");
			else
				new_command(line, env, &i, cmd);
		}
	}
	return (cmd);
}
