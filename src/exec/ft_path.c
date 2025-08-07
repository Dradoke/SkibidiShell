/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skibidi_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
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
		{
			i = 0;
			while (tab[i])
				free(tab[i++]);
			return (free(tab), path);
		}
		free(path);
		i++;
	}
	return (NULL);
}

char	*ft_path(t_shell *sh, t_cmd *cmd)
{
	char	**tab;
	char	*cmd_name;

	tab = ft_split(ft_getenv_val(sh->env, "PATH"), ':');
	cmd_name = ((t_arg *)cmd->arg->content)->name;
	if (cmd_name[0] == '/' || cmd_name[0] == '.')
	{
		if (access(cmd_name, X_OK) == 0)
			return (cmd_name);
		else
			return (ft_seterror(sh, FTERR_PATH, FTERR_PATH_VAL), NULL);
	}
	else
		return (found_path(sh, cmd_name, tab));
}
