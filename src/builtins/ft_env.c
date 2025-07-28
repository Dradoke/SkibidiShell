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

// int ft_env(t_list *args, t_list **env)
// {
// 	(void)args;
// 	t_list	*env_lst;

// 	env_lst = env;
// 	if (!env_lst) 
// 		return (printf("Erreur : liste vide ou allocation échouée\n"), 1);
// 	while (env_lst)
// 	{
// 		ft_printf("%s", ((t_env *)env_lst->content)->key);
// 		ft_printf("=", ((t_env *)env_lst->content)->key,((t_env *)env_lst->content)->value);
// 		ft_printf("%s\n", ((t_env *)env_lst->content)->value);
// 		env_lst = env_lst->next;
// 	}
// 	return (0);
// }