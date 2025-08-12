/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:22 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:12:23 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

static void	ft_clean_heredoc(t_shell *sh, char *line, int fd)
{
	close(fd);
	free(line);
	ft_free_all(&sh);
}

static t_bool	heredoc_child(t_shell *sh, t_redir *redir)
{
	char	*line;

	signal(SIGINT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printfd(2, FTERR_HDOC_D, redir->name);
			return (ft_clean_heredoc(sh, line, redir->fd), FALSE);
		}
		if (!ft_strncmp(redir->name, line, ft_strlen(redir->name) + 1))
			return (ft_clean_heredoc(sh, line, redir->fd), exit(0), TRUE);
		ft_printfd(redir->fd, "%s\n", line);
		free(line);
	}
}

static t_bool	make_heredoc(t_shell *sh, t_redir *redir)
{
	int		pid;
	int		status;

	redir->hdoc_path = ft_strjoin_free(ft_strdup("/tmp/"), ft_rand_str(10));
	redir->fd = open(redir->hdoc_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd < 0)
		return (ft_seterror(sh, FTERR_OPEN, 1), FALSE);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (close(redir->fd), FALSE);
	if (pid == 0)
	{
		heredoc_child(sh, redir);
		exit(0);
	}
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	close(redir->fd);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (ft_printfd(STDOUT_FILENO, "\n"), FALSE);
	if (WEXITSTATUS(status) != 0)
		return (FALSE);
	return (TRUE);
}

t_bool	ft_heredoc(t_shell *sh, t_list *cmd)
{
	t_list	*redir;

	redir = ((t_cmd *)cmd->content)->redir;
	while (cmd)
	{
		while (redir)
		{
			if (((t_redir *)redir->content)->type == HEREDOC)
			{
				if (!make_heredoc(sh, redir->content))
					return (FALSE);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (TRUE);
}
