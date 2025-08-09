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
	char	*cmd_name;

	signal(SIGINT, SIG_DFL);
	if (!setup_redir(sh, cmd) && (ft_puterror(sh), 1))
		exit(1);
	setup_pipes_and_redir(sh, cmd);
	if (!cmd->arg)
		exit(0);
	cmd_name = ((t_arg *)cmd->arg->content)->name;
	if (is_builtins(cmd_name, sh->bultins))
		exit(ft_builtins(sh, cmd));
	path = ft_path(sh, cmd);
	arg = ft_argtoarray(cmd->arg);
	env = ft_envtoarray(sh->env);
	if (!path)
		handle_no_path(cmd_name);
	else
		execve(path, arg, env);
	if (path)
		handle_execve_error(path, cmd_name);
	(free(path), free(arg), free(env));
	exit(get_exit_code(path));
}

static t_bool	single_critical_case(t_shell *sh, t_cmd *cmd)
{
	int	std_fd[2];

	if (sh->cmd->next || !((t_cmd *)sh->cmd->content)->arg)
		return (FALSE);
	if (!is_critical(((t_cmd *)sh->cmd->content)->arg))
		return (FALSE);
	if (!setup_redir(sh, cmd))
		return (free(sh->last_err), sh->last_err = ft_itoa(1),
			ft_puterror(sh), TRUE);
	std_fd[INPUT] = dup(STDIN_FILENO);
	std_fd[OUTPUT] = dup(STDOUT_FILENO);
	if (cmd->last_redir[INPUT])
		dup2(cmd->last_redir[INPUT]->fd, STDIN_FILENO);
	if (cmd->last_redir[OUTPUT])
		dup2(cmd->last_redir[OUTPUT]->fd, STDOUT_FILENO);
	free(sh->last_err);
	sh->last_err = ft_itoa(ft_builtins(sh, cmd));
	dup2(std_fd[INPUT], STDIN_FILENO);
	dup2(std_fd[OUTPUT], STDOUT_FILENO);
	close(std_fd[INPUT]);
	close(std_fd[OUTPUT]);
	close_all_fd(cmd->redir);
	return (TRUE);
}

static void	wait_all_pids(t_shell *sh, t_list *cmds)
{
	t_list	*cmd_i;
	int		status;
	t_bool	is_pipe;

	cmd_i = cmds;
	is_pipe = FALSE;
	while (cmd_i)
	{
		waitpid(((t_cmd *)cmd_i->content)->pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGPIPE)
			{
				is_pipe = TRUE;
				sh->err.code = 141;
			}
		}
		cmd_i = cmd_i->next;
	}
	if (is_pipe)
		ft_putstr_fd("\n", 2);
	if (WIFEXITED(status))
		sh->err.code = WEXITSTATUS(status);
	free(sh->last_err);
	sh->last_err = ft_itoa(sh->err.code);
}

static t_bool	ft_exec_loop(t_shell *sh)
{
	t_list	*cmd_i;
	t_cmd	*cmd_content;

	cmd_i = sh->cmd;
	signal(SIGINT, SIG_IGN);
	while (cmd_i)
	{
		cmd_content = cmd_i->content;
		if (cmd_i->next && pipe(sh->pipe_new) < 0)
			return (ft_seterror(sh, FTERR_PIPE, 2), FALSE);
		cmd_content->pid = fork();
		if (cmd_content->pid < 0)
			return (ft_seterror(sh, FTERR_FORK, 2), FALSE);
		if (cmd_content->pid == 0)
			execute_cmd(sh, cmd_content);
		if (cmd_i->next)
			switch_pipes(&sh->pipe_new, &sh->pipe_old);
		cmd_i = cmd_i->next;
	}
	signal(SIGINT, sigint_handler);
	return (TRUE);
}

t_bool	ft_exec(t_shell *sh)
{
	init_pipes(sh);
	if (single_critical_case(sh, sh->cmd->content))
		return (TRUE);
	if (!ft_exec_loop(sh))
		return (FALSE);
	if (sh->pipe_old[INPUT] != -1)
		close(sh->pipe_old[INPUT]);
	if (sh->pipe_old[OUTPUT] != -1)
		close(sh->pipe_old[OUTPUT]);
	wait_all_pids(sh, sh->cmd);
	return (TRUE);
}
