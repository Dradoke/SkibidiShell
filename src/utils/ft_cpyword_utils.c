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

static int	get_var_len(char *line)
{
	int	i;

	i = 0;
	while (!ft_isspace(line[i]) && !ft_isdelim(line[i]) && line[i] != '\''
		&& line[i] != '\"' && line[i] != '$'
		&& (ft_isalnum(line[i]) || line[i] == '_') && line[i])
		i++;
	return (i);
}

// Maybe fixed
int	ft_get_env_size(t_shell *sh, char *line, t_quotes_verif quotes)
{
	int	j;
	int	var_len;

	j = 1;
	if (!line[j])
		return (0);
	if (ft_isspace(line[j]) || ft_isdelim(line[j]))
		return (j++, 1);
	var_len = get_var_len(&line[j]);
	if (ft_isdigit(line[j]))
		return (sh->i++);
	if (line[j] == '$')
		return (sh->i++);
	while (sh->env)
	{
		if (ft_strncmp_cstm(&line[j], ((t_env *)sh->env->content)->key, var_len) == 0)
		{
			if (quotes == SIMPLE)
			{
				return (sh->i += (var_len),
					j += var_len + 1,
					(int)ft_strlen(((t_env *)sh->env->content)->key));
			}
			else if (quotes == DOUBLE || quotes == NONE)
				return (sh->i += (var_len),
					j += (int)ft_strlen(((t_env *)sh->env->content)->value),
					(int)ft_strlen(((t_env *)sh->env->content)->value));
		}
		sh->env = sh->env->next;
	}
	sh->i += (var_len);
	return (1);
}

bool	ft_write_env(char *line, int *k, t_word *word, t_quotes_verif *quotes)
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
	var_len = get_var_len(&line[1]);
	j = 0;
	if (ft_isdigit(line[i]))
		return ((*word->i)++, (*word->j)--);
	while (word->env)
	{
		env_var = (t_env *)word->env->content;
		if (ft_strncmp_cstm(&line[i], env_var->key, var_len) == 0)
		{
			if ((*quotes) == SIMPLE)
			{
				ft_memset(&word->word[(*k)++], '$', 1);
				while (*k < var_len && env_var->key[j])
					ft_memset(&word->word[(*k)++], env_var->key[j++], 1);
			}
			else if ((*quotes) == DOUBLE || (*quotes) == NONE)
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

// Compares up to n characters of two strings lexicographically.
// Returns <0 if s1 < s2, 0 if s1 = s2, >0 if s1 > s2.
// Comparison is done using unsigned characters.
// Also compare the len of s2 with n, return len of s2 if not the same.
int	ft_strncmp_cstm(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n != ft_strlen(s2))
		return (ft_strlen(s2));
	while (i < n && (str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

bool	quotes_usecase(char c, t_quotes_verif *quotes)
{
	if ((c == '\"' && *(quotes) == NONE)
		|| (c == '\'' && *(quotes) == NONE)
		|| (c == '\"' && *(quotes) == DOUBLE)
		|| (c == '\'' && *(quotes) == SIMPLE))
		return (true);
	else
		return (false);
}
