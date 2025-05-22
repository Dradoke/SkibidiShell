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

#include "../../include/skibidi_shell.h"

static char	*get_env_key(char *line)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	str = ft_calloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '=')
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*get_env_value(char *line)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (line[i] == '=')
		i++;
	j = i;
	while (line[i])
		i++;
	str = ft_calloc(sizeof(char) * (i - j + 1));
	if (!str)
		return (NULL);
	i = j;
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	return (str);
}

/*Build the chained list of env variables, give a key(env name) and a value
  Return a t_list**/
t_list	*ft_env_to_lst(char **envp)
{
	t_list	*env_lst;
	t_list	*new;
	t_env	*env;
	int		i;

	i = 0;
	env_lst = NULL;
	while (envp[i])
	{
		env = ft_calloc(sizeof(t_env) * 1);
		if (!env)
			return (NULL);
		env->key = get_env_key(envp[i]);
		env->value = get_env_value(envp[i]);
		new = ft_lstnew(env);
		if (!new)
			return (NULL);
		new->index = i;
		ft_lstadd_back(&env_lst, new);
		i++;
	}
	return (env_lst);
}
