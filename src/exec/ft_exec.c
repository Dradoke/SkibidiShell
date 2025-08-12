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

static void	execute_execve(t_shell *sh, t_cmd *cmd, char *cmd_name)
{
	char	*path;
	char	**arg;
	char	**env;
	int		code;

	path = ft_path(sh, cmd);
	arg = ft_argtoarray(cmd->arg);
	env = ft_envtoarray(sh->env);
	if (path)
	{
		execve(path, arg, env);
		handle_execve_error(path, cmd_name);
	}
	close_all_fd(cmd->redir);
	ft_free_all(&sh);
	code = get_exit_code(path);
	ft_vfree(2, &path, &arg);
	ft_free_array(env);
	exit(code);
}

static void	execute_cmd(t_shell *sh, t_cmd *cmd)
{
	char	*cmd_name;
	int		code;

	signal(SIGINT, SIG_DFL);
	if (!setup_redir(sh, cmd) && (ft_puterror(sh), 1))
		exit(1);
	setup_pipes_and_redir(sh, cmd);
	if (!cmd->arg)
		exit(0);
	cmd_name = ((t_arg *)cmd->arg->content)->name;
	if (is_builtins(cmd_name, sh->bultins))
	{
		code = ft_builtins(sh, cmd);
		close_all_fd(cmd->redir);
		ft_free_all(&sh);
		exit(code);
	}
	execute_execve(sh, cmd, cmd_name);
}

static t_bool	single_critical_case(t_shell *sh, t_cmd *cmd)
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
	close(sh->std_fd[INPUT]);
	close(sh->std_fd[OUTPUT]);
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
