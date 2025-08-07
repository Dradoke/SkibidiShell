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

static void	execute_cmd(t_shell *sh, t_cmd *cmd)
{
	char	*path;
	char	**arg;
	char	**env;

	setup_pipes_and_redir(sh, cmd);
	if (is_builtins(((t_arg *)cmd->arg->content)->name, sh->bultins))
	{
		ft_builtins(sh, cmd);
		exit(EXIT_SUCCESS);
	}
	path = ft_path(sh, cmd);
	arg = ft_argtoarray(cmd->arg);
	env = ft_envtoarray(sh->env);
	execve(path, arg, env);
	free(path);
	free(arg);
	free(env);
	exit(EXIT_FAILURE);
}

static t_bool	single_critical_case(t_shell *sh, t_cmd *cmd)
{
	int	std_fd[2];

	if (!sh->cmd->next && is_critical(((t_cmd *)sh->cmd->content)->arg))
	{
		if (!setup_redir(sh->cmd->content))
			return (ft_seterror(sh, FTERR_OPEN, 2), FALSE);
		std_fd[INPUT] = dup(STDIN_FILENO);
		std_fd[OUTPUT] = dup(STDOUT_FILENO);
		if (cmd->last_redir[INPUT])
			dup2(cmd->last_redir[INPUT]->fd, STDIN_FILENO);
		if (cmd->last_redir[OUTPUT])
			dup2(cmd->last_redir[OUTPUT]->fd, STDOUT_FILENO);
		ft_builtins(sh, cmd);
		dup2(std_fd[INPUT], STDIN_FILENO);
		dup2(std_fd[OUTPUT], STDOUT_FILENO);
		close(std_fd[INPUT]);
		close(std_fd[OUTPUT]);
		close_all_fd(cmd->redir);
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	ft_exec_loop(t_shell *sh, t_list *cmd_i, t_cmd *cmd_content)
{
	while (cmd_i)
	{
		cmd_content = cmd_i->content;
		if (cmd_i->next)
			if (pipe(sh->pipe_new) < 0)
				return (ft_seterror(sh, FTERR_PIPE, 2), FALSE);
		if (!setup_redir(cmd_content))
			return (ft_seterror(sh, FTERR_OPEN, 2), FALSE);
		cmd_content->pid = fork();
		if (cmd_content->pid < 0)
			return (ft_seterror(sh, FTERR_FORK, 2), FALSE);
		if (cmd_content->pid == 0)
			execute_cmd(sh, cmd_content);
		close_all_fd(cmd_content->redir);
		if (sh->pipe_old[INPUT] != -1)
			close(sh->pipe_old[INPUT]);
		if (sh->pipe_new[OUTPUT] != -1)
			close(sh->pipe_new[OUTPUT]);
		if (cmd_i->next)
			switch_pipes(&sh->pipe_new, &sh->pipe_old);
		cmd_i = cmd_i->next;
	}
	return (TRUE);
}

t_bool	ft_exec(t_shell *sh)
{
	t_list	*cmd_i;
	t_cmd	*cmd_content;

	init_pipes(sh);
	cmd_i = sh->cmd;
	cmd_content = cmd_i->content;
	if (single_critical_case(sh, cmd_i->content))
		return (TRUE);
	if (!ft_exec_loop(sh, cmd_i, cmd_content))
		return (FALSE);
	wait_all_pids(sh, sh->cmd);
	return (TRUE);
}
