/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:02 by mavander          #+#    #+#             */
/*   Updated: 2025/08/13 20:12:46 by ngaudoui         ###   ########.fr       */
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
		return (ft_printfd(STDERR_FILENO, FTERR_ENV),
			FTERR_ENV_VAL);
	while (env_lst)
	{
		key = ((t_env *)env_lst->content)->key;
		value = ((t_env *)env_lst->content)->value;
		ft_printfd(STDOUT_FILENO, "declare -x %s=%s\n", key, value);
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

static int	process_export_arg(t_list **env, t_arg *env_arg)
{
	char	*env_key;

	if (!is_valid_key(env_arg->name))
		return (1);
	if (ft_strchr(env_arg->name, '='))
	{
		env_key = get_env_key(env_arg->name);
		if (ft_strcmp(env_key, "_") == 0)
			return (0);
		ft_set_new_env(env, env_key, env_arg);
		free(env_key);
	}
	return (0);
}

int	ft_export(t_shell *sh, t_list **env, t_cmd *cmd)
{
	t_list	*args;
	t_arg	*env_arg;
	int		ret;

	(void)sh;
	args = cmd->arg->next;
	ret = 0;
	if (!args)
		return (print_env(env));
	while (args)
	{
		env_arg = ((t_arg *)args->content);
		ret = process_export_arg(env, env_arg);
		args = args->next;
	}
	if (ret == 1)
		ft_printfd(2, FTERR_EXP);
	return (ret);
}
