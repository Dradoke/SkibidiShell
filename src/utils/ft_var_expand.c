/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpyword_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

// Returns the len of a string
// Complying with the rules of env variables format rules
// 1st char has to be alphabetic OR an underscore '_'
// The rest has to be either alphanumeric or underscores
// If an invalid char is encountered, len until this char will be returned
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

// Searches the string {key} up until the {key_len}th char in the t_list env
// Returns the t_env where the KEY is identical
// Returns NULL if not found
t_env	*search_env(char *key, size_t key_len, t_list *env)
{
	t_env	*env_var;

	if (!key || !env || key_len <= 0)
		return (NULL);
	while (env)
	{
		env_var = (t_env *)env->content;
		if (env_var && env_var->key)
			if (ft_strlen(env_var->key) == (size_t)key_len
				&& ft_strncmp(env_var->key, key, key_len) == 0)
				return (env_var);
		env = env->next;
	}
	return (NULL);
}

// Counts the size of the value assigned to the specified key in t_list env
//
// We use {key} to find the corresponding value
// We search for it in the {env} linked list of type t_list
// Increases {i} by the {key}'s length (excluding $)
//
// Returns the {key}'s value length
size_t	ft_get_env_size(char *key, t_list *env, size_t *i)
{
	int		key_len;
	t_env	*env_var;

	if (!key[0] || ft_isspace(key[1]) || ft_isdelim(key[1]))
		return (1);
	if (key[0] == '?')
		return ((*i)++, 0);
	if (key[0] == '$')
		return ((*i)++, 0);
	key_len = get_key_len(&key[1]);
	env_var = search_env(&key[1], env, key_len);
	if (env_var && env_var->value)
		return (*i += key_len, ft_strlen(env_var->value));
	return (*i += key_len, 0);
}

// Writes the value assigned to the key following in src
bool	ft_write_env(t_shell *sh, char *src, char *dst, size_t *i, t_list *env)
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
