/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:13:22 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:13:23 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

// Complies with the rules of env variables format rules
// 1st char has to be alphabetic OR an underscore '_'
// The rest has to be either alphanumeric or underscores
// If an invalid char is encountered, len until this char will be returned
//
// Return:
// length of an env var key
//
// NO ERROR HANDLING NEEDED
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
//
// Return:
// t_env where the KEY is identical
// NULL if not found
//
// NO ERROR HANDLING NEEDED
static t_env	*search_env(char *key, size_t key_len, t_list *env)
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
// Return:
// {key}'s value length
//
// NO ERROR HANDLING NEEDED
size_t	ft_get_env_size(t_shell *sh, char *src, size_t *i)
{
	size_t	key_len;
	t_env	*env_var;

	if (!sh->last_err)
		sh->last_err = ft_strdup("0");
	if (src[0] == '?')
		return ((*i)++, ft_strlen(sh->last_err));
	else if (ft_isalpha(src[0]) || src[0] == '_')
	{
		key_len = get_key_len(src);
		env_var = search_env(src, key_len, sh->env);
		*i += key_len;
		if (env_var && env_var->value)
			return (ft_strlen(env_var->value));
		return (0);
	}
	return (1);
}

// Writes the value assigned to the key following in src
//
// NO ERROR HANDLING NEEDED
t_bool	ft_write_env(t_shell *sh, char *src, char *dst, size_t *i)
{
	size_t	key_len;
	t_env	*env_var;

	if (src[0] == '?')
		return (ft_strcpy(dst, sh->last_err), (*i)++, TRUE);
	else if (ft_isalpha(src[0]) || src[0] == '_')
	{
		key_len = get_key_len(src);
		env_var = search_env(src, key_len, sh->env);
		*i += key_len;
		if (env_var && env_var->value)
			ft_strcpy(dst, env_var->value);
		return (TRUE);
	}
	dst[0] = '$';
	dst[1] = '\0';
	return (TRUE);
}
