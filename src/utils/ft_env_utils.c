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

/*Return the env value if the key exist
  Take the env list and a key*/
char	*ft_getenv_val(t_list *env, char *key)
{
	t_list	*env_tmp;

	env_tmp = env;
	while ((env_tmp))
	{
		if (ft_strcmp(((t_env *)(env_tmp)->content)->key, key) == 0)
			return (((t_env *)(env_tmp)->content)->value);
		(env_tmp) = (env_tmp)->next;
	}
	return (NULL);
}

t_env	*ft_getenv(t_list *env, char *key)
{
	t_list	*env_tmp;

	env_tmp = env;
	while ((env_tmp))
	{
		if (ft_strcmp(((t_env *)(env_tmp)->content)->key, key) == 0)
			return (((t_env *)env_tmp->content));
		(env_tmp) = (env_tmp)->next;
	}
	return (NULL);
}
