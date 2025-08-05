/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

static t_bool	set_pipes(int *pipes[2][2])
{
	if (!pipe(pipes[INFILE]) && !pipe(pipes[OUTFILE]));
		return (TRUE);
	return (FALSE);
}

static t_bool	setup_redir(t_cmd *cmd)
{
	t_list	*redir_i;
	t_redir	*redir_content;
	char	*name;
	int		fd;

	redir_i = cmd->redir;
	while (redir_i)
	{
		redir_content = ((t_redir *)redir_i->content);
		name = redir_content->name;
		if (redir_content->type == APPEND)
			fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else if (redir_content->type == OUTFILE)
			fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (redir_content->type == INFILE)
			fd = open(name, O_RDONLY | O_CREAT);
		else if (redir_content->type == HEREDOC)
			fd = open(name, O_RDONLY);
		if (fd < 0)
			return (FALSE);
		redir_content->fd = fd;
		redir_i = redir_i->next;
	}
	return (TRUE);
}

static t_bool	close_all_fd(t_list *redir)
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

void wait_all_pids(t_shell *sh, t_list *cmd)
{
	int 	status;
	int		pid;

	while (cmd)
	{
		pid = ((t_cmd *)cmd->content)->pid;
		waitpid(pid, &status, 0);
		sh->last_err = ft_itoa(WEXITSTATUS(status));
		cmd = cmd->next;
	}
}

t_bool	execute_cmd(t_shell *sh, t_cmd *cmd)
{
	dup2(cmd->last_redir[INFILE], INFILE);
	dup2(cmd->last_redir[OUTFILE], OUTFILE);
	if (is_builtins(((t_arg *)cmd->arg->content)->name, sh->bultins))
		ft_builtins();
	else
		execve();
}

single_critical_case(t_shell *sh)
{
	if (!sh->cmd->next && is_critical(((t_cmd *)sh->cmd->content)->arg))
	{
		if (!setup_redir(sh->cmd->content))
			return (ft_seterror(sh, FTERR_OPEN, 2), FALSE);
		exec_builtin(sh->cmd->content);
		close_all_fd(((t_cmd *)sh->cmd->content)->redir);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	ft_exec(t_shell *sh)
{
	t_list	*cmd_i;
	t_cmd	*cmd_content;

	cmd_i = sh->cmd;
	if (single_critical_case(sh))
		return (TRUE);
	while (cmd_i)
	{
		cmd_content = cmd_i->content;
		if (!setup_redir(cmd_i->content));
			return (ft_seterror(sh, FTERR_OPEN, 2), FALSE);
		execute_cmd(sh, cmd_content);
		close_all_fd(cmd_content->redir);
		cmd_i = cmd_i->next;
	}
	wait_all_pids(sh, sh->cmd);
}
