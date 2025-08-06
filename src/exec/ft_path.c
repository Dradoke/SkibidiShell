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

char	*ft_path(t_shell *sh, t_cmd *cmd)
{
	int		i;
	char	**tab;
	char	*cmd_name;
	char	*path;

	i = 0;
	tab = ft_split(ft_getenv_val(sh->env, "PATH"), ':');
	cmd_name = ((t_arg *)cmd->arg->content)->name;
	while (i < get_nb_cmd(ft_getenv_val(sh->env, "PATH")))
	{
		path = NULL;
		path = ft_strjoin(tab[i], "/");
		path = ft_strjoin(path, cmd_name);
		if (access(path, X_OK) == 0)
		{
			i = 0;
			while (tab[i])
				free(tab[i++]);
			return (free(tab), path);
		}
		i++;
	}
	return (NULL);
}
