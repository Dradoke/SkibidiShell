/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:25 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:12:26 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

static int	get_nb_cmd(char *tab)
{
	int	i;
	int	nb_cmd;

	i = 0;
	nb_cmd = 0;
	while (tab[i])
	{
		if (tab[i] == ':')
			nb_cmd++;
		i++;
	}
	return (nb_cmd + 1);
}

static char	*found_path(t_shell *sh, char *cmd_name, char **tab)
{
	int		i;
	char	*path;
	char	*path_tmp;

	i = 0;
	while (i < get_nb_cmd(ft_getenv_val(sh->env, "PATH")))
	{
		path_tmp = ft_strjoin(tab[i], "/");
		path = ft_strjoin(path_tmp, cmd_name);
		free(path_tmp);
		if (access(path, X_OK) == 0)
			return (ft_free_array(tab), path);
		free(path);
		i++;
	}
	ft_printfd(2, FTERR_CMD, cmd_name);
	return (ft_free_array(tab), NULL);
}

static char	*get_currpath_cmd(char *cmd_name)
{
	char		*curr_path;
	char		*path_tmp;

	(void)cmd_name;
	curr_path = getcwd(NULL, 0);
	path_tmp = curr_path;
	curr_path = ft_strjoin(path_tmp, "/");
	free(path_tmp);
	path_tmp = curr_path;
	curr_path = ft_strjoin(path_tmp, cmd_name);
	free(path_tmp);
	if (access(curr_path, X_OK) == 0)
	{
		return (curr_path);
	}
	else
	{
		free(curr_path);
		return (NULL);
	}
}

char	*ft_path(t_shell *sh, t_cmd *cmd)
{
	char		**tab;
	char		*cmd_name;
	char		*curr_path;
	t_env		*path;

	if (!cmd->arg || !((t_arg *)cmd->arg->content)->name)
		return (NULL);
	cmd_name = ((t_arg *)cmd->arg->content)->name;
	if (cmd_name[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd_name, '/') != NULL)
		return (ft_strdup(cmd_name));
	path = ft_getenv(sh->env, "PATH");
	if (!path)
	{
		curr_path = get_currpath_cmd(cmd_name);
		if (curr_path)
			return (curr_path);
		free(curr_path);
		ft_printfd(2, FTERR_PATH, cmd_name);
		return (free(path), NULL);
	}
	tab = ft_split(ft_getenv_val(sh->env, "PATH"), ':');
	return (found_path(sh, cmd_name, tab));
}

int	is_directory(const char *path)
{
	struct stat	st;

	return (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
}
