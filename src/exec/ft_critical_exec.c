/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_critical_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:17 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:12:18 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

static void	close_fd_and_std(t_shell *sh, t_cmd *cmd)
{
	close(sh->std_fd[INPUT]);
	close(sh->std_fd[OUTPUT]);
	close_all_fd(cmd->redir);
}

t_bool	single_critical_case(t_shell *sh, t_cmd *cmd)
{
	int	code;

	if (sh->cmd->next || !((t_cmd *)sh->cmd->content)->arg)
		return (FALSE);
	if (!is_critical(((t_cmd *)sh->cmd->content)->arg))
		return (FALSE);
	if (!setup_redir(sh, cmd))
	{
		free(sh->last_err);
		sh->last_err = ft_itoa(1);
		return (ft_puterror(sh), TRUE);
	}
	sh->std_fd[INPUT] = dup(STDIN_FILENO);
	sh->std_fd[OUTPUT] = dup(STDOUT_FILENO);
	if (cmd->last_redir[INPUT])
		dup2(cmd->last_redir[INPUT]->fd, STDIN_FILENO);
	if (cmd->last_redir[OUTPUT])
		dup2(cmd->last_redir[OUTPUT]->fd, STDOUT_FILENO);
	code = ft_builtins(sh, cmd);
	free(sh->last_err);
	sh->last_err = ft_itoa(code);
	dup2(sh->std_fd[INPUT], STDIN_FILENO);
	dup2(sh->std_fd[OUTPUT], STDOUT_FILENO);
	close_fd_and_std(sh, cmd);
	return (TRUE);
}
