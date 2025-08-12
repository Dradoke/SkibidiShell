/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:13:04 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 22:12:42 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

void	handle_execve_error(char *path, char *cmd_name)
{
	if (errno == ENOENT)
	{
		if (cmd_name[0] == '.')
			ft_printfd(2, FTERR_PATH,
				cmd_name);
		else if (ft_strchr(cmd_name, '/'))
			ft_printfd(2, FTERR_PATH, cmd_name);
		else
			ft_printfd(2, FTERR_CMD, cmd_name);
	}
	else if (errno == EACCES)
	{
		if (is_directory(path))
			ft_printfd(2, FTERR_ISDIR, cmd_name);
		else
			ft_printfd(2, FTERR_PERM, cmd_name);
	}
	else
		ft_printfd(2, FTERR_CMD, cmd_name);
}

void	handle_no_path(char *cmd_name)
{
	if (cmd_name[0] == '.' && cmd_name[1] == '/')
		ft_printfd(2, FTERR_ISDIR, cmd_name);
	else if (ft_strchr(cmd_name, '/'))
		ft_printfd(2, FTERR_PATH, cmd_name);
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
