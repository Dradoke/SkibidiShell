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
	int i;

	i = 0;
	while (!ft_isspace(line[i]) && !ft_isdelim(line[i]) && line[i] != '\'' && line[i] != '\"')
	{
		printf("char of var_len: %c\n", line[i]);
		i++;
	}
	return (i);
}

int	ft_get_env_size(t_word *word, char *line, t_quotes_verif quotes, int *i)
{
	int j;
	int	var_len;
	t_list	*start;
	(void)i;

	j = 0;
	start = word->env;
	if (ft_isspace(line[j + 1]) || ft_isdelim(line[j + 1]))
		return (1);
	j++;
	var_len = get_var_len(line);
	printf("LINE: %s\n", line);
	printf("Var_len: %d\n", var_len);

	while (word->env)
	{
		printf("line word: %s, key : %s\n", &line[j], ((t_env *)word->env->content)->key);
		if (ft_strncmp(&line[j], ((t_env *)word->env->content)->key, var_len - 1) == 0)
		{
			printf("STRNCMP OK\n");
			if (quotes == SIMPLE)
			{
				printf("SIZE of var_len: %d\n", var_len);
				printf("SIZE of key: %d\n", (int)ft_strlen(((t_env *)word->env->content)->key));
				return (word->env = start,
					(*i) += (var_len),
					(*word->j) += var_len,
					(int)ft_strlen(((t_env *)word->env->content)->key));
			}
			else if (quotes == DOUBLE || quotes == NONE)
				return (word->env = start,
					(*i) += (var_len),
					(*word->j) += (int)ft_strlen(((t_env *)word->env->content)->value),
					(int)ft_strlen(((t_env *)word->env->content)->value));
		}
		word->env = word->env->next;
	}
	return (word->env = start, 0);
}

bool	ft_write_env(char *line, int *k, t_word *word, t_quotes_verif *quotes)
{
	int	i;
	int	j;
	int	var_len;
	t_env	*env_var;

	i = 1;
	printf("Write env: %s\n", line);
	printf("Write word: %s\n", word->word);
	printf("Write word: %s\n", &line[i]);
	if (ft_isspace(line[i]) || ft_isdelim(line[i]))
		return (ft_memset(&word->word[(*k)++], '$', 1), true);
	var_len = get_var_len(line);
	j = 0;
	while (word->env)
	{
		env_var = (t_env *)word->env->content;
		printf("line word: %s, key : %s\n", &line[i], env_var->key);
		if (ft_strncmp(&line[i], env_var->key, var_len) == 0)
		{
			printf("STRNCMP WRITE ENV OK\n");
			if ((*quotes) == SIMPLE)
			{
				ft_memset(&word->word[(*k)++], '$', 1);
				while (*k < var_len && env_var->key[j])
					ft_memset(&word->word[(*k)++], env_var->key[j++], 1);
			}
			else if ((*quotes) == DOUBLE || (*quotes) == NONE)
			{
				while (*k < (int)ft_strlen(env_var->value) && env_var->value[j])
					ft_memset(&word->word[(*k)++], env_var->value[j++], 1);
			}
			return (j);
		}
		word->env = word->env->next;
	}
	printf("Write word: %s\n", word->word);
	return (j);
}
