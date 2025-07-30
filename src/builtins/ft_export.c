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



int	ft_export(t_list *args, t_list **env)
{
	t_list	*arg_lst;
	t_env	*new_env;
	t_arg	*env_arg;
	char	*env_key;

	arg_lst = args->next;
	if (!arg_lst)
		return (ft_env(args, env), 0); // !!! CHANGER !!!: doit print les variables d'environnement comme bash le fait.
	env_arg = ((t_arg *)arg_lst->content);
	if (is_valid_env(env_arg->name, 'e') == FALSE)
		return (ft_putstr_fd(FTERR_EXP"\n", STDIN_FILENO), FTERR_EXP_VAL);
	env_key = get_env_key(env_arg->name);
	if (ft_getenv(*env, env_key))
		new_env = ft_getenv(*env, env_key);
	else
	{
		new_env = calloc(1, sizeof(t_env *));
		new_env->key = get_env_key(env_arg->name);
		ft_lstadd_back(env, ft_lstnew(new_env));
	}
	new_env->value = get_env_value(env_arg->name);
	free(env_key);
	return (0);
}
