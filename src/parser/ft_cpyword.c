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

#include "skibidi_shell.h"

static void free_word(t_word *word)
{
	if (word->j)
	{
		word->j = NULL;
		free(word->j);
	}
	if (word->word)
	{
		word->word = NULL;
		free(word->word);
	}
	if (word)
	{
		word = NULL;
		free(word);
	}
}
/*	Verify the quote statement between DOUBLE, SIMPLE, and NONE
	Take a char, the quote type and a boolean
	boolean: true = erase the quote, false = let the quote*/
static void	quotes_verif(char *c, t_quotes_verif *quotes, bool del_quote)
{
	if ((*c) == '\"' && (*quotes) == NONE)
		(*quotes) = DOUBLE;
	else if ((*c) == '\'' && (*quotes) == NONE)
		(*quotes) = SIMPLE;
	else if ((((*c) == '\"' && (*quotes) == DOUBLE)
			|| ((*c) == '\'' && (*quotes) == SIMPLE)))
		(*quotes) = NONE;
	(void)del_quote;
	// if (del_quote == true && ((*quotes == SIMPLE && *c == '\'') || (*quotes == DOUBLE && *c == '"')))
	// 	(*c) = '\0';
}

static char	*allocate_string(char *line, t_word *word, t_quotes_verif *quotes)
{
	int				i;
	char			*str;
	t_list			*start;

	i = (*word->i);
	start = word->env;
	word->j = ft_calloc(sizeof(int) * 1);
	if (!word->j)
		return (NULL);
	printf("DEBUG: word_len = %d\n", (*word->j));
	printf("DEBUG: word_char = %c\n", line[i]);
	printf("DEBUG: QUOTES = %d\n", *quotes);
	printf("-----------------------------\n");
	while (line[i] && ((!ft_isdelim(line[i]) && !ft_isspace(line[i]))
			|| (*quotes) == SIMPLE || (*quotes) == DOUBLE))
	{
		if (quotes_usecase(line[i], quotes))
			quotes_verif(&line[i], quotes, false);
		else if (line[i] == '$')
		{
			ft_get_env_size(word, &line[i], (*quotes), &i);
			word->env = start;
		}
		else if (!ft_isspace(line[i]) || (*quotes != NONE))
			(*word->j)++;
		printf("DEBUG: word_char = %c\n", line[i]);
		printf("DEBUG: word_len = %d\n", (*word->j));
		i++;
		ft_printf("DEBUG: QUOTES = %d\n", *quotes);
	}
	str = ft_calloc(sizeof(char) * (*word->j + 1));
	if (!str)
		return (free_word(word), NULL);
	return (str);
}

static void	strlcpy(char *line, t_word *word, t_quotes_verif *quotes)
{
	int	k;

	k = 0;
	printf("Valeur de i avant copy: %d et value: %c\n", (*word->i), line[*word->i]);
	printf("Valeur de j avant copy: %d\n", (*word->j));
	printf("J: %d\n", (*word->j));
	while (line[(*word->i)] && ((!ft_isdelim(line[(*word->i)]) && !ft_isspace(line[(*word->i)]))
			|| (*quotes) == SIMPLE || (*quotes) == DOUBLE))
	{
		if (quotes_usecase(line[(*word->i)], quotes))
			quotes_verif(&line[(*word->i)++], quotes, true);
		else if (line[(*word->i)] == '$')
		{
			printf("DEBUG: quotes = %d\n", *quotes);
			ft_write_env(&line[(*word->i)], &k, word, quotes);
		}
		else
			word->word[k++] = line[(*word->i)++];
	}
	if (ft_isdelim(line[(*word->i)]) && *word->j == 0)  // Peut etre supprimer apres tests ?
		(*word->i)++;
	word->word[k] = '\0';
}

/*Copy a word until the next delimiter or space
  Return 0 if no error*/
char	*ft_cpyword(char *line, size_t *i, t_list *env)
{
	t_quotes_verif	quotes;
	t_word		*word;

	word = ft_calloc(sizeof(t_word) * 1);
	if (!word)
		return (NULL);
	quotes = NONE;
	word->i = (int *)i;
	word->env = env;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	printf("ALLOCATE STRING\n\n");
	word->word = allocate_string(line, word, &quotes);
	if (!word->word)
		return (free_word(word), NULL);
	if (quotes != NONE)
		return (free_word(word), free(line), ft_printf("ERREUR DE QUOTES\n"), NULL); // Changer le ft_printf par la fonction d'erreur, erreur de quotes !
	printf("STRLCPY\n\n");
	strlcpy(line, word, &quotes);
	printf("VALEUR DE i: %ld\n", *i);
	if (!word->word)
		return (free_word(word), NULL);								// Changer le return par la fonction d'erreur, erreur d'allocation !
	printf("Word: %s\n", word->word);
	free_word(word);
	return (word->word);
}
