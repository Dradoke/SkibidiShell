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

static int	print_env(t_list **env)
{
	t_list	*env_lst;
	char	*key;
	char	*value;

	env_lst = *env;
	if (!env_lst)
		return (ft_putstr_fd(FTERR_ENV"\n", STDERR_FILENO), FTERR_ENV_VAL);
	while (env_lst)
	{
		key = ((t_env *)env_lst->content)->key;
		value = ((t_env *)env_lst->content)->value;
		ft_printfd(STDOUT_FILENO, "declare -x %s", key);
		ft_printfd(STDOUT_FILENO, "=");
		ft_printfd(STDOUT_FILENO, "%s\n", value);
		env_lst = env_lst->next;
	}
	return (EXIT_SUCCESS);
}

static void	ft_set_new_env(t_list **env, char *env_key, t_arg *env_arg)
{
	t_env	*new_env;

	new_env = ft_getenv(*env, env_key);
	if (!new_env)
	{
		new_env = ft_calloc(1 * sizeof(t_env));
		new_env->key = get_env_key(env_arg->name);
		ft_lstadd_back(env, ft_lstnew(new_env));
	}
	else
		free(new_env->value);
	new_env->value = get_env_value(env_arg->name);
}

int	ft_export(t_shell *sh, t_list **env, t_cmd *cmd)
{
	t_list	*args;
	t_arg	*env_arg;
	char	*env_key;

	(void)sh;
	args = cmd->arg->next;
	if (!args)
		return (print_env(env));
	while (args)
	{
		env_arg = ((t_arg *)args->content);
		if (is_valid_env(env_arg->name, 'e') == FALSE)
			return (ft_putstr_fd(FTERR_EXP"\n", STDERR_FILENO), FTERR_EXP_VAL);
		env_key = get_env_key(env_arg->name);
		ft_set_new_env(env, env_key, env_arg);
		free(env_key);
		args = args->next;
	}
	return (EXIT_SUCCESS);
}
