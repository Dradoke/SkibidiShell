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

int	ft_unset(t_shell *sh, t_list **env)
{
	t_list	*env_lst;
	t_list	*args;
	char	*key;

	args = ((t_cmd *)sh->cmd->content)->arg;
	if (!args->next)
		return (0);
	env_lst = *env;
	if (is_valid_env(((t_arg *)args->next->content)->name, 'u') == FALSE)
		return (ft_putstr_fd(FTERR_UNSET"\n", STDIN_FILENO), FTERR_UNSET_VAL);
	key = get_env_key(((t_arg *)args->next->content)->name);
	while (env_lst)
	{
		if (ft_strcmp(((t_env *)env_lst->content)->key, key) == 0)
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
