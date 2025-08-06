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

int	ft_unset(t_shell *sh, t_list **env)
{
	t_list	*env_lst;
	t_list	*args;
	char	*key;

	args = ((t_cmd *)sh->cmd->content)->arg->next;
	if (!args->next)
		return (0);
	env_lst = *env;
	while (args)
	{
		if (is_valid_env(((t_arg *)args->content)->name, 'u') == FALSE)
			return (ft_putstr_fd(FTERR_UNSET"\n", STDERR_FILENO),
				FTERR_UNSET_VAL);
		key = get_env_key(((t_arg *)args->content)->name);
		envlst_iter(sh, env, env_lst, key);
		free(key);
		args = args->next;
	}
	return (0);
}
