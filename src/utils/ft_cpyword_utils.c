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
// Fixed
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

// Fixed
t_env	*search_env(t_list *env, char *key, int key_len)
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
		{
			if (ft_strlen(env_var->key) == (size_t)key_len
				&& ft_strncmp(env_var->key, key, key_len) == 0)
				return (env_var);
		}
		cur = cur->next;
	}
	return (NULL);
}

// Fixed
size_t	ft_get_env_size(char *word, size_t *i, t_list *env, t_quote quote)
{
	int		key_len;
	t_env	*env_var;

	*i++;
	if (!word[1] || ft_isspace(word[1]))
		return (1);
	if (word[1] == '?')
		return (*i++, ft_strlen(ft_itoa(last_exit_status())));
	if (word[1] == '$')
		return (*i++, ft_strlen(ft_itoa(ft_get_pid())));
	key_len = get_key_len(&word[1]);
	env_var = search_env(env, &word[1], key_len);
	if (env_var && env_var->value)
		return (*i += key_len, ft_strlen(env_var->value));
	return (*i += key_len, 0);
}

bool	ft_write_env(char *line, int *k, t_word *word, t_quote *quote)
{
	int		i;
	int		j;
	int		var_len;
	t_env	*env_var;
	t_list	*start;

	i = 1;
	if (ft_isspace(line[i]) || ft_isdelim(line[i]))
		return (ft_memset(&word->word[(*k)++], '$', 1), (*word->i)++, true);
	start = word->env;
	var_len = get_key_len(&line[1]);
	j = 0;
	if (ft_isdigit(line[i]))
		return ((*word->i)++, (*word->j)--);
	while (word->env)
	{
		env_var = (t_env *)word->env->content;
		if (ft_strncmp_cstm(&line[i], env_var->key, var_len) == 0)
		{
			if ((*quote) == SINGLE)
			{
				ft_memset(&word->word[(*k)++], '$', 1);
				while (*k < var_len && env_var->key[j])
					ft_memset(&word->word[(*k)++], env_var->key[j++], 1);
			}
			else if ((*quote) == DOUBLE || (*quote) == NONE)
			{
				while (*k < (*word->j) && env_var->value[j])
					ft_memset(&word->word[(*k)++], env_var->value[j++], 1);
				*word->i += var_len + 1;
			}
			return (word->env = start, j);
		}
		word->env = word->env->next;
	}
	return ((*word->i) += (var_len + 1), word->env = start, j);
}
