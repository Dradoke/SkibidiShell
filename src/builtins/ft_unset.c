/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:08 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:12:09 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

static void	unset_env(t_shell *sh, t_list **env, t_list *target)
{
	t_env	*env_node;

	(void)sh;
	env_node = ((t_env *)target->content);
	if (!target->prev)
	{
		*env = target->next;
		if (target->next)
			target->next->prev = NULL;
	}
	else
	{
		if (target->prev)
			target->prev->next = target->next;
		if (target->next)
			target->next->prev = target->prev;
	}
	free(env_node->key);
	free(env_node->value);
	free(env_node);
	free(target);
}

static void	envlst_iter(t_shell *sh, t_list **env, t_list *env_lst, char *key)
{
	t_env	*env_node;

	while (env_lst)
	{
		env_node = (env_lst->content);
		if (ft_strcmp(env_node->key, key) == 0)
		{
			unset_env(sh, env, env_lst);
			break ;
		}
		env_lst = env_lst->next;
	}
	env_lst = *env;
}

int	ft_unset(t_shell *sh, t_list **env, t_cmd *cmd)
{
	t_list	*env_lst;
	t_list	*args;
	char	*key;

	args = cmd->arg;
	if (!args->next)
		return (0);
	args = cmd->arg->next;
	env_lst = *env;
	while (args)
	{
		if (!is_valid_key(((t_arg *)args->content)->name))
			return (ft_printfd(2, FTERR_UNSET), 2);
		key = get_env_key(((t_arg *)args->content)->name);
		envlst_iter(sh, env, env_lst, key);
		free(key);
		args = args->next;
	}
	return (0);
}
