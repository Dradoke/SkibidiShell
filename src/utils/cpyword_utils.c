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
	return (i - 1);
}

int	ft_get_env_size(t_word *word, char *line, t_quotes_verif quotes, int *j)
{
	int i;
	int	var_len;
	t_list	*start;

	i = 0;
	start = word->env;
	if (ft_isspace(line[i + 1]) || ft_isdelim(line[i + 1]))
		return (1);
	var_len = get_var_len(line);
	printf("LINE: %s\n", line);

	while (word->env)
	{
		printf("line word: %s, key : %s\n", &line[i + 1], ((t_env *)word->env->content)->key);
		if (ft_strncmp(&line[i + 1], ((t_env *)word->env->content)->key, var_len) == 0)
		{
			printf("STRNCMP OK\n");
			if (quotes == SIMPLE)
			{
				printf("SIZE of var_len: %d\n", var_len);
				printf("SIZE of key: %d\n", (int)ft_strlen(((t_env *)word->env->content)->key));
				return (word->env = start,
					(*j) += (var_len),
					(*word->j) += (int)ft_strlen(((t_env *)word->env->content)->key),
					(int)ft_strlen(((t_env *)word->env->content)->key));
			}
			else if (quotes == DOUBLE || quotes == NONE)
				return (word->env = start,
					(*j) += (var_len),
					(*word->j) += (int)ft_strlen(((t_env *)word->env->content)->value),
					(int)ft_strlen(((t_env *)word->env->content)->value));
		}
			word->env = word->env->next;
	}
	return (word->env = start, 0);
}
