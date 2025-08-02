/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

char	**ft_argtoarray(t_list *list)
{
	char	**array;
	int		i;

	i = 0;
	array = ft_calloc(ft_lstsize(list));
	while (list)
	{
		array[i++] = ((t_arg *)list->content)->name;
		list = list->next;
	}
	return (array);
}

char	**ft_envtoarray(t_list *list)
{
	char	**array;
	char	*env;
	int		i;

	i = 0;
	array = ft_calloc(ft_lstsize(list));
	while (list)
	{
		env = ft_strjoin(((t_env *)list->content)->key, "=");
		env = ft_strjoin(env, ((t_env *)list->content)->value);
		array[i++] = env;
		list = list->next;
	}
	return (array);
}
