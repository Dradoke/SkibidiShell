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
	array = ft_calloc(ft_lstsize(list) + 1);
	while (list)
	{
		array[i++] = ((t_arg *)list->content)->name;
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_envtoarray(t_list *list)
{
	char	**array;
	char	*env_tmp;
	char	*env;
	int		i;

	i = 0;
	array = ft_calloc(ft_lstsize(list) + 1);
	while (list)
	{
		env_tmp = ft_strjoin(((t_env *)list->content)->key, "=");
		env = ft_strjoin(env_tmp, ((t_env *)list->content)->value);
		free(env_tmp);
		array[i++] = env;
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}
