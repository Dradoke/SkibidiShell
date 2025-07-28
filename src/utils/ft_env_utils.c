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

void	ft_setenv(t_list *env, char *key, char *value)
{
	t_list	*env_tmp;

	env_tmp = env;
	while ((env_tmp))
	{
		if (ft_strcmp(((t_env *)(env_tmp)->content)->key, key) == 0)
		{
			free(((t_env *)(env_tmp)->content)->value);
			((t_env *)(env_tmp)->content)->value = ft_strdup(value);
			break ;
		}
		(env_tmp) = (env_tmp)->next;
	}
}

char	*ft_getenv(t_list *env, char *key)
{
	t_list	*env_tmp;

	env_tmp = env;
	while ((env_tmp))
	{
		if (ft_strcmp(((t_env *)(env_tmp)->content)->key, key) == 0)
		{
			printf("JE SUIS SUR SHELL !!!\n");
			return (((t_env *)(env_tmp)->content)->value);
		}
		(env_tmp) = (env_tmp)->next;
	}
	return (NULL);
}
