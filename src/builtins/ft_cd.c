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

int ft_cd(t_list *args, t_list **env)
{
	char *new_pwd;
	char *old_pwd;

	if (!((t_arg *)args->next->content)->name)
		return (1); //AJOUTER L'ERREUR  FTERR_CD
	if (chdir(((t_arg *)args->next->content)->name) != 0)
		return (1); //AJOUTER L'ERREUR  FTERR_CD
	free(ft_getenv(*env, "OLDPWD"));
	old_pwd = ft_getenv(*env, "PWD");
	new_pwd = getcwd(NULL, 0);
	ft_setenv(*env, "OLDPWD", old_pwd);
	ft_setenv(*env, "PWD", new_pwd);
	return (0);
}
