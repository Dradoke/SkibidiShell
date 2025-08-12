/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoarray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:13:13 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:13:14 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

char	**ft_argtoarray(t_list *arg)
{
	char	**array;
	int		i;

	i = 0;
	array = ft_calloc((ft_lstsize(arg) + 1) * sizeof(char *));
	while (arg)
	{
		array[i++] = ((t_arg *)arg->content)->name;
		arg = arg->next;
	}
	array[i] = NULL;
	return (array);
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

char	**ft_envtoarray(t_list *env_lst)
{
	char	**array;
	char	*env_tmp;
	char	*env;
	int		i;

	i = 0;
	array = ft_calloc((ft_lstsize(env_lst) + 1) * sizeof(char *));
	while (env_lst)
	{
		env_tmp = ft_strjoin(((t_env *)env_lst->content)->key, "=");
		env = ft_strjoin(env_tmp, ((t_env *)env_lst->content)->value);
		free(env_tmp);
		array[i++] = env;
		env_lst = env_lst->next;
	}
	array[i] = NULL;
	return (array);
}
