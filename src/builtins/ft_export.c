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


static int print_env(t_list **env)
{
	t_list	*env_lst;

	env_lst = *env;
	if (!env_lst) 
		return (ft_putstr_fd(FTERR_ENV"\n", STDOUT_FILENO), FTERR_ENV_VAL);
	while (env_lst)
	{
		ft_printf("declare -x %s", ((t_env *)env_lst->content)->key);
		ft_printf("=");
		ft_printf("%s\n", ((t_env *)env_lst->content)->value);
		env_lst = env_lst->next;
	}
	return (EXIT_SUCCESS);
}


int	ft_export(t_shell *sh, t_list **env)
{
	t_list	*args;
	t_env	*new_env;
	t_arg	*env_arg;
	char	*env_key;

	args = ((t_cmd *)sh->cmd->content)->arg->next;
	if (!args)
		return (print_env(env)); // !!! CHANGER !!!: doit print les variables d'environnement comme bash le fait.
	env_arg = ((t_arg *)args->content);
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
	if (new_env->value)
		free(new_env->value);
	new_env->value = get_env_value(env_arg->name);
	free(env_key);
	return (EXIT_SUCCESS);
}
