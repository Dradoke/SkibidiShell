/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpyword.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/skibidi_shell.h"

static void free_word(t_word *word)
{
	if (word->j)
		free(word->j);
	if (word->word)
		free(word->word);
	if (word)
		free(word);
}

static void	quotes_verif(char *c, t_quotes_verif *quotes)
{
	if ((*c) == '\"' && (*quotes) == NONE)
	{
		(*quotes) = DOUBLE;
		(*c) = '\0';
	}
	else if ((*c) == '\'' && (*quotes) == NONE)
	{
		(*quotes) = SIMPLE;
		(*c) = '\0';
	}
	else if ((((*c) == '\"' && (*quotes) == DOUBLE)
			|| ((*c) == '\'' && (*quotes) == SIMPLE)))
	{
		(*quotes) = NONE;
		(*c) = '\0';
	}
}

static char	*allocate_string(char *line, t_word *word, t_quotes_verif *quotes)
{
	int				i;
	int				env_len;
	char			*str;

	
	i = (*word->i);
	word->j = ft_calloc(sizeof(int) * 1);
	if (!word->j)
		return (NULL);
	while (line[i] && ((!ft_isdelim(line[i]) && !ft_isspace(line[i]))
			|| (*quotes) == SIMPLE || (*quotes) == DOUBLE))
	{
		if (line[i] == '\"' || line[i] == '\'')
			quotes_verif(&line[i], quotes);
		else if (line[i] == '$')
			env_len += ft_get_env_size(word, &line[i], (*quotes), &i);
		else if (!ft_isspace(line[i]) || (*quotes != NONE))
			(*word->j)++;
		printf("DEBUG: word_len = %d\n", (*word->j));
		printf("DEBUG: word_char = %c\n", line[i]);
		i++;
	}
	str = ft_calloc(sizeof(char) * (*word->j + 1));
	if (!str)
		return (free_word(word), NULL);
	return (str);
}

static void	strlcpy(char *line, t_word *word)
{
	int	k;
	k = 0;
	if (*(word->j) > 0)
	{
		while (k < ((*word->j)))
		{
			if (line[(*word->i)] != '\0')
				word->word[k++] = line[(*word->i)];
			(*word->i)++;
		}
		word->word[k] = '\0';
	}
	(*word->i)++;
}

/*Copy a word until the next delimiter or space
  Return 0 if no error*/
bool	ft_cpyword(char *line, int *i, t_list *env)
{
	t_quotes_verif	quotes;
	t_word		*word;

	word = ft_calloc(sizeof(t_word) * 1);
	if (!word)
		return (1);
	quotes = NONE;
	word->i = i;
	word->env = env;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	word->word = allocate_string(line, word, &quotes);
	if (!word->word)
		return (free_word(word), 1);
	strlcpy(line, word);
	printf("VALEUR DE i: %d\n", *i);
	if (!word->word)
		return (free_word(word), 1);								// Changer le return par la fonction d'erreur, erreur d'allocation !
	if (quotes != NONE)
		return (free_word(word), free(line), ft_printf("ERREUR DE QUOTES\n")); // Changer le ft_printf par la fonction d'erreur, erreur de quotes !
	printf("Word: %s\n", word->word);
	free_word(word);
	free(line);
	return (0);
}
