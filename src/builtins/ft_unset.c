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

int ft_unset(t_list *args, t_list **env)
{
	t_list	*env_lst;
	char *key;
	char *value;

	if (!args->next)
		return (0);
	env_lst = *env;
	key = get_env_key(((t_arg *)args->next->content)->name);
	value = get_env_value(((t_arg *)args->next->content)->name);
	while (((t_env *)env_lst->content)->key)
	{
		if (ft_strcmp(((t_env *)env_lst->content)->key, key) == 0);
		{
			env_lst->prev->next = env_lst->next;
			env_lst->next->prev = env_lst->prev;
			free(((t_env *)env_lst->content)->key);
			free(((t_env *)env_lst->content)->value);
			free(env_lst->content);
			break ;
		}
		env_lst = env_lst->next;
	}
	return (0);
}
