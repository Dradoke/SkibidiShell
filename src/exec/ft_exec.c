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
			fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir_content->type == OUTFILE)
			fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir_content->type == INFILE)
			fd = open(name, O_RDONLY);
		else if (redir_content->type == HEREDOC)
		{
			ft_printfd(1, "%s\n", redir_content->hdoc_path);
			fd = open(redir_content->hdoc_path, O_RDONLY);
		}
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

static void	wait_all_pids(t_shell *sh, t_list *cmd)
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

static void	setup_pipes_and_redir(t_shell *sh, t_cmd *cmd)
{
	if (cmd->last_redir[INPUT])
		dup2(cmd->last_redir[INPUT]->fd, STDIN_FILENO);
	if (cmd->last_redir[OUTPUT])
		dup2(cmd->last_redir[OUTPUT]->fd, STDOUT_FILENO);
	if (sh->pipe_old[INPUT] != -1)
		dup2(sh->pipe_old[INPUT], STDIN_FILENO);
	if (sh->pipe_new[OUTPUT] != -1)
		dup2(sh->pipe_new[OUTPUT], STDOUT_FILENO);
	if (sh->pipe_old[INPUT] != -1)
		close(sh->pipe_old[INPUT]);
	if (sh->pipe_old[OUTPUT] != -1)
		close(sh->pipe_old[OUTPUT]);
	if (sh->pipe_new[INPUT] != -1)
		close(sh->pipe_new[INPUT]);
	if (sh->pipe_new[OUTPUT] != -1)
		close(sh->pipe_new[OUTPUT]);
}

void	execute_cmd(t_shell *sh, t_cmd *cmd)
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

t_bool	single_critical_case(t_shell *sh, t_cmd *cmd)
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

static void	switch_pipes(int (*pipe_new)[2], int (*pipe_old)[2])
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

static void	init_pipes(t_shell *sh)
{
	sh->pipe_old[INPUT] = -1;
	sh->pipe_old[OUTPUT] = -1;
	sh->pipe_new[INPUT] = -1;
	sh->pipe_new[OUTPUT] = -1;
}

t_bool	ft_exec(t_shell *sh)
{
	t_list	*cmd_i;
	t_cmd	*cmd_content;

	init_pipes(sh);
	cmd_i = sh->cmd;
	if (single_critical_case(sh, cmd_i->content))
		return (TRUE);
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
		if (cmd_i->next)
			switch_pipes(&sh->pipe_new, &sh->pipe_old);
		cmd_i = cmd_i->next;
	}
	wait_all_pids(sh, sh->cmd);
	return (TRUE);
}
