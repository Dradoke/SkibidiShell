/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:11:57 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:11:58 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

int	ft_env(t_shell *sh, t_list **env, t_cmd *cmd)
{
	t_list	*env_lst;
	t_env	*env_node;

	(void)sh;
	(void)cmd;
	env_lst = *env;
	if (!env_lst)
		return (ft_printfd(STDERR_FILENO, FTERR_ENV), FTERR_ENV_VAL);
	while (env_lst)
	{
		if ((t_env *)env_lst->content)
		{
			env_node = ((t_env *)env_lst->content);
			ft_printfd(STDOUT_FILENO, "%s", env_node->key);
			ft_printfd(STDOUT_FILENO, "=");
			ft_printfd(STDOUT_FILENO, "%s\n", env_node->value);
		}
		env_lst = env_lst->next;
	}
	return (0);
}
