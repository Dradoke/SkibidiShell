/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:51 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:12:52 by mavander         ###   ########.fr       */
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
