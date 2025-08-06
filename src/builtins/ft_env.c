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
	t_env	*env_node;

	(void)sh;
	env_lst = *env;
	if (!env_lst)
		return (ft_putstr_fd(FTERR_ENV"\n", STDERR_FILENO), FTERR_ENV_VAL);
	while (env_lst)
	{
		if ((t_env *)env_lst->content)
		{
			env_node = ((t_env *)env_lst->content);
			ft_printfd(STDOUT_FILENO, "%s", env_node->key);
			ft_printfd(STDOUT_FILENO, "=");
			ft_printfd(STDOUT_FILENO, "%s\n", env_node->value);
		}
		env_lst = env_lst->next;
	}
	return (0);
}
