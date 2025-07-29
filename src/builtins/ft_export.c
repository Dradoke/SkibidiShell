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

static bool have_equal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true) ;
		i++;
	}
	return (false);
}
// static bool is_valid_key(char *str)
// {
// 	if (ft_isalpha(str[0]) == false && str[0] != '_');
// }
int ft_export(t_list *args, t_list **env)
{
	t_list *arg_lst;
	t_env *new_env;

	arg_lst = args->next;
	if (!((t_arg *)args->next->content)->name)
		return (ft_putstr_fd(FTERR_UNSET"\n", STDIN_FILENO), FTERR_UNSET_VAL);
	if (ft_isalpha(((t_arg *)args->next->content)->name[0]) == false)
		return (ft_putstr_fd(FTERR_UNSET"\n", STDIN_FILENO), FTERR_UNSET_VAL);
	if (have_equal(((t_arg *)args->next->content)->name) == false)
		return (ft_putstr_fd(FTERR_UNSET"\n", STDIN_FILENO), FTERR_UNSET_VAL);
	new_env = calloc(1 ,sizeof(new_env));
	new_env->key = get_env_key(((t_arg *)arg_lst->content)->name);
	new_env->value = get_env_value(((t_arg *)arg_lst->content)->name);
	ft_lstadd_back(env, ft_lstnew(new_env));
	return (0);
}
