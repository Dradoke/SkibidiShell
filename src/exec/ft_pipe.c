/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:28 by mavander          #+#    #+#             */
/*   Updated: 2025/08/13 21:13:07 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

t_bool	setup_redir(t_shell *sh, t_cmd *cmd)
{
	t_list	*redir_i;
	t_redir	*redir_content;
	char	*name;
	int		fd;

	(void)sh;
	redir_i = cmd->redir;
	while (redir_i)
	{
		redir_content = ((t_redir *)redir_i->content);
		name = redir_content->name;
		if (redir_content->type == APPEND)
			fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir_content->type == OUTFILE)
			fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir_content->type == INFILE)
			fd = open(name, O_RDONLY);
		else if (redir_content->type == HEREDOC)
			fd = open(redir_content->hdoc_path, O_RDONLY);
		if (fd < 0)
			return (ft_printfd(STDERR_FILENO, " %s\n", strerror(errno)), FALSE);
		redir_content->fd = fd;
		redir_i = redir_i->next;
	}
	return (TRUE);
}

void	setup_pipes_and_redir(t_shell *sh, t_cmd *cmd)
{
	if (!cmd->last_redir[INPUT] && sh->pipe_old[INPUT] != -1)
		dup2(sh->pipe_old[INPUT], STDIN_FILENO);
	if (!cmd->last_redir[OUTPUT] && sh->pipe_new[OUTPUT] != -1)
		dup2(sh->pipe_new[OUTPUT], STDOUT_FILENO);
	if (cmd->last_redir[INPUT])
		dup2(cmd->last_redir[INPUT]->fd, STDIN_FILENO);
	if (cmd->last_redir[OUTPUT])
		dup2(cmd->last_redir[OUTPUT]->fd, STDOUT_FILENO);
	if (sh->pipe_old[INPUT] != -1)
		close(sh->pipe_old[INPUT]);
	if (sh->pipe_old[OUTPUT] != -1)
		close(sh->pipe_old[OUTPUT]);
	if (sh->pipe_new[INPUT] != -1)
		close(sh->pipe_new[INPUT]);
	if (sh->pipe_new[OUTPUT] != -1)
		close(sh->pipe_new[OUTPUT]);
	close_all_fd(cmd->redir);
}

void	switch_pipes(int (*pipe_new)[2], int (*pipe_old)[2])
{
	if ((*pipe_old)[INPUT] != -1)
		close((*pipe_old)[INPUT]);
	if ((*pipe_old)[OUTPUT] != -1)
		close((*pipe_old)[OUTPUT]);
	(*pipe_old)[INPUT] = (*pipe_new)[INPUT];
	(*pipe_old)[OUTPUT] = (*pipe_new)[OUTPUT];
	(*pipe_new)[INPUT] = -1;
	(*pipe_new)[OUTPUT] = -1;
}

void	init_pipes(t_shell *sh)
{
	sh->pipe_old[INPUT] = -1;
	sh->pipe_old[OUTPUT] = -1;
	sh->pipe_new[INPUT] = -1;
	sh->pipe_new[OUTPUT] = -1;
}
