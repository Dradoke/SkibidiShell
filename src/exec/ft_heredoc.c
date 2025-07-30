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

static t_bool	heredoc_child(t_redir *redir)
{
	char *line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (ft_printf(FTERR_HDOC_D"\n", redir->name), exit(0), FALSE);
		if (!ft_strncmp(redir->name, line, ft_strlen(redir->name) + 1))
			return (free(line), exit(0), TRUE);
		write(redir->fd, line, ft_strlen(line));
		write(redir->fd, "\n", 1);
		free(line);
	}
}

static t_bool	make_heredoc(t_redir *redir)
{
	int		pid;
	int		status;

	redir->hdoc_path = ft_strjoin("/tmp/", ft_rand_str(10));
	redir->fd = open(redir->hdoc_path, O_WRONLY | O_CREAT | O_TRUNC);
	pid = fork();
	if (pid < 0)
		return (FALSE);
	if (pid == 0)
		heredoc_child(redir);
	waitpid(pid, &status, 0);
	close(redir->fd);
	if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
		return (FALSE);
	return (TRUE);

}

t_bool	ft_heredoc(t_list *cmd)
{
	t_list	*redir;

	redir = ((t_cmd *)cmd->content)->redir;
	while (cmd)
	{
		while (redir)
		{
			if (((t_redir *)redir->content)->type == HEREDOC)
			{
				if (!make_heredoc(redir->content))
					return (FALSE);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (TRUE);
}
