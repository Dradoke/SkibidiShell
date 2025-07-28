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

static size_t	get_key_len(char *s)
{
	size_t	i;

	i = 0;
	if (!s || !(ft_isalpha(s[i]) || s[i] == '_'))
		return (i);
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (i);
		i++;
	}
	return (i);
}

t_env	*search_env(char *key, t_list *env, int key_len)
{
	t_list	*cur;
	t_env	*env_var;

	if (!env || !key || key_len <= 0)
		return (NULL);
	cur = env;
	while (cur)
	{
		env_var = (t_env *)cur->content;
		if (env_var && env_var->key)
			if (ft_strlen(env_var->key) == (size_t)key_len
				&& ft_strncmp(env_var->key, key, key_len) == 0)
				return (env_var);
		cur = cur->next;
	}
	return (NULL);
}

size_t	ft_get_env_size(char *key, size_t *i, t_list *env)
{
	int		key_len;
	t_env	*env_var;

	(*i)++;
	if (!key[1] || ft_isspace(key[1]) || ft_isdelim(key[1]))
		return (1);
	if (key[1] == '?')
		return ((*i)++, 0);
	if (key[1] == '$')
		return ((*i)++, 0);
	key_len = get_key_len(&key[1]);
	env_var = search_env(&key[1], env, key_len);
	if (env_var && env_var->value)
		return (*i += key_len, ft_strlen(env_var->value));
	return (*i += key_len, 0);
}

bool	ft_write_env(char *src, char *dst, size_t *i, t_list *env)
{
	int		key_len;
	t_env	*env_var;

	(*i)++;
	if (!src[1] || ft_isspace(src[1]) || ft_isdelim(src[1]))
		return (dst[0] = '$', 1);
	if (src[1] == '?')
		return ((*i)++, 1);
	if (src[1] == '$')
		return ((*i)++, 1);
	key_len = get_key_len(&src[1]);
	env_var = search_env(&src[1], env, key_len);
	*i += key_len;
	if (env_var && env_var->value)
		ft_strcpy(dst, env_var->value);
	return (1);
}
