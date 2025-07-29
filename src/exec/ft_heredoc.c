/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

static bool	make_heredoc(t_redir *redir)
{
	char	*line;

	redir->hdoc_path = ft_strjoin("/tmp/", ft_rand_str(10));
	redir->fd = open(redir->hdoc_path, O_WRONLY | O_CREAT | O_TRUNC);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (close(redir->fd), false);
		if (!ft_strncmp(redir->name, line, ft_strlen(redir->name) + 1))
			return (true);
		write(redir->fd, line, ft_strlen(line));
		write(redir->fd, "\n", 1);
	}
}

bool	ft_heredoc(t_list *cmd)
{
	t_list	*redir;

	redir = ((t_cmd *)cmd->content)->redir;
	while (cmd)
	{
		while (redir)
		{
			if (((t_redir *)redir->content)->type == HEREDOC)
			{
				make_heredoc(redir->content);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
