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

int	ft_env(t_shell *sh, t_list **env)
{
	t_list	*env_lst;

	(void)sh;
	env_lst = *env;
	if (!env_lst)
		return (ft_putstr_fd(FTERR_ENV"\n", STDOUT_FILENO), FTERR_ENV_VAL);
	while (env_lst)
	{
		ft_printfd(STDOUT_FILENO, "%s", ((t_env *)env_lst->content)->key);
		ft_printfd(STDOUT_FILENO, "=");
		ft_printfd(STDOUT_FILENO, "%s\n", ((t_env *)env_lst->content)->value);
		env_lst = env_lst->next;
	}
	return (0);
}
