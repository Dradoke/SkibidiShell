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

void	handle_execve_error(char *path, char *cmd_name)
{
	if (errno == ENOENT)
	{
		if (cmd_name[0] == '.')
			ft_printfd(2, "minishell: %s: No such file or directory\n",
				cmd_name);
		else if (ft_strchr(cmd_name, '/'))
			ft_printfd(2, "minishell: %s: No such file or directory\n",
				cmd_name);
		else
			ft_printfd(2, "minishell: %s: command not found\n", cmd_name);
	}
	else if (errno == EACCES)
	{
		if (is_directory(path))
			ft_printfd(2, "minishell: %s: Is a directory\n", cmd_name);
		else
			ft_printfd(2, "minishell: %s: Permission denied\n", cmd_name);
	}
	else
		ft_printfd(2, "minishell: %s: command not found\n", cmd_name);
}

void	handle_no_path(char *cmd_name)
{
	if (cmd_name[0] == '.' && cmd_name[1] == '/')
		ft_printfd(2, "minishell: %s: Is a directory\n", cmd_name);
	else if (ft_strchr(cmd_name, '/'))
		ft_printfd(2, "minishell: %s: No such file or directory\n",
			cmd_name);
}

int	get_exit_code(char *path)
{
	if (!path)
		return (127);
	if (errno == EACCES)
		return (126);
	if (errno == EACCES)
		return (126);
	if (errno == ENOENT)
		return (127);
	return (127);
}

t_bool	close_all_fd(t_list *redir)
{
	t_redir	*redir_content;

	while (redir)
	{
		redir_content = redir->content;
		close(redir_content->fd);
		redir = redir->next;
	}
	return (TRUE);
}
