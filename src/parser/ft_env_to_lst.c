/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:43 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:12:44 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

/*PARSING PART !
  Return the key from the env array, like USER=user_name,
  The function will return USER*/
char	*get_env_key(char *line)
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

/*PARSING PART !
  Return the value from the env array, like USER=user_name,
  The function will return user_name*/
char	*get_env_value(char *line)
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

// Builds the linked list of env variables
// Gives a key and a value
// Returns a t_list *
t_list	*ft_env_to_lst(t_shell *sh, char **envp)
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
			return (ft_seterror(sh, FTERR_ALLOC, 2), NULL);
		env->key = get_env_key(envp[i]);
		env->value = get_env_value(envp[i]);
		if (!env->key || !env->value)
			return (ft_seterror(sh, FTERR_ALLOC, 2), NULL);
		new = ft_lstnew(env);
		if (!new)
			return (ft_seterror(sh, FTERR_ALLOC, 2), NULL);
		new->index = i++;
		ft_lstadd_back(&env_lst, new);
	}
	return (env_lst);
}
