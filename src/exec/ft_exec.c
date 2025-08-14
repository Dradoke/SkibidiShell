/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:20 by mavander          #+#    #+#             */
/*   Updated: 2025/08/14 18:49:48 by mavander         ###   ########.fr       */
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

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (!setup_redir(sh, cmd) && (close_all_fd(cmd->redir), 1)
		&& (close_pipes(sh), 1) && (ft_puterror(sh), 1)
		&& (ft_free_all(&sh), 1))
		exit(1);
	setup_pipes_and_redir(sh, cmd);
	if (!cmd->arg && (close_pipes(sh), 1) && (close_all_fd(cmd->redir), 1)
		&& (ft_free_all(&sh), 1))
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

static void	wait_all_pids(t_shell *sh, t_list *cmds)
{
	t_list	*cmd_i;
	int		status;

	cmd_i = cmds;
	while (cmd_i)
	{
		waitpid(((t_cmd *)cmd_i->content)->pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT && (ft_printfd(1, "\n"), 1))
				sh->err.code = 130;
			if (WTERMSIG(status) == SIGPIPE)
				sh->err.code = 141;
			if (WTERMSIG(status) == SIGQUIT && (ft_printfd(2, "Quit\n"), 1))
				sh->err.code = 131;
		}
		cmd_i = cmd_i->next;
	}
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
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	return (TRUE);
}
