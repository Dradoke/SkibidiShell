/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

t_bool	close_all_fd(t_list *redir)
{
	t_redir	*redir_content;

	while (redir)
	{
		redir_content = redir->content;
		if (close(redir_content->fd) < 0)
			return (FALSE);
		redir = redir->next;
	}
	return (TRUE);
}

void	wait_all_pids(t_shell *sh, t_list *cmd)
{
	int	status;
	int	pid;

	while (cmd)
	{
		pid = ((t_cmd *)cmd->content)->pid;
		if (pid > 0)
		{
			waitpid(pid, &status, 0);
			free(sh->last_err);
			sh->last_err = ft_itoa(WEXITSTATUS(status));
		}
		cmd = cmd->next;
	}
}
