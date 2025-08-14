/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:11:51 by mavander          #+#    #+#             */
/*   Updated: 2025/08/14 15:02:49 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

int	ft_cd(t_shell *sh, t_list **env, t_cmd *cmd)
{
	char	*new_pwd;
	char	*old_pwd;
	t_list	*args;

	(void)sh;
	args = cmd->arg->next;
	if (!args)
	{
		if (ft_getenv_val(*env, "HOME") == NULL)
			return (ft_printfd(STDERR_FILENO, FTERR_NOTHOME), FTERR_CD_VAL);
		if (chdir(ft_getenv_val(*env, "HOME")) != 0)
			return (ft_printfd(STDERR_FILENO, FTERR_CD), FTERR_CD_VAL);
	}
	else if (args->next)
		return (ft_printfd(2, FTERR_ARGS), 1);
	else if (!((t_arg *)args->content)->name)
		return (ft_printfd(STDERR_FILENO, FTERR_CD), FTERR_CD_VAL);
	else if (chdir(((t_arg *)args->content)->name) != 0)
		return (ft_printfd(STDERR_FILENO, FTERR_CD), FTERR_CD_VAL);
	old_pwd = ft_getenv_val(*env, "PWD");
	new_pwd = getcwd(NULL, 0);
	ft_setenv(*env, "OLDPWD", old_pwd);
	ft_setenv(*env, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}
