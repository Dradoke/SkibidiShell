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

int	ft_cd(t_shell *sh, t_list **env)
{
	char	*new_pwd;
	char	*old_pwd;
	t_list	*args;

	args = ((t_list *)((t_cmd *)sh->cmd->content)->arg)->next;
	if (!((t_arg *)args->content)->name)
		return (ft_putstr_fd(FTERR_CD"\n", STDOUT_FILENO), FTERR_CD_VAL);
	if (chdir(((t_arg *)args->content)->name) != 0)
		return (ft_putstr_fd(FTERR_CD"\n", STDOUT_FILENO), FTERR_CD_VAL);
	old_pwd = ft_getenv_val(*env, "PWD");
	new_pwd = getcwd(NULL, 0);
	ft_setenv(*env, "OLDPWD", old_pwd);
	ft_setenv(*env, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}
