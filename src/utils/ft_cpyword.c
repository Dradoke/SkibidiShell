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
	if (del_quote == true)
		(*c) = '\0';
}

static char	*allocate_string(char *line, t_word *word, t_quotes_verif *quotes)
{
	int				i;
	int				env_len;
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
		if (line[i] == '\"' || line[i] == '\'')
			quotes_verif(&line[i], quotes, false);
		else if (line[i] == '$')
		{
			env_len += ft_get_env_size(word, &line[i], (*quotes), &i);
			word->env = start;
		}
		else if (!ft_isspace(line[i]) || (*quotes != NONE))
			(*word->j)++;
		printf("DEBUG: word_len = %d\n", (*word->j));
		printf("DEBUG: word_char = %c\n", line[i]);
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

	k = -1;
	printf("Valeur de i avant copy: %d et value: %c\n", (*word->i), line[*word->i]);

	printf("J: %d\n", (*word->j));
	while (k < (*word->j) || (*quotes) == SIMPLE || (*quotes) == DOUBLE)
	{
		if (k == -1)
			k = 0;
		if (line[(*word->i)] == '\'' || line[(*word->i)] == '\"')
			quotes_verif(&line[(*word->i)++], quotes, true);
		else if (line[(*word->i)] == '$')
		{
			printf("DEBUG: quotes = %d\n", *quotes);
			ft_write_env(&line[(*word->i)], &k, word, quotes);
		}
		else
			word->word[k++] = line[(*word->i)++];
		// if (word->word[k])
		// (*word->i)++;
	}
	word->word[k] = '\0';
	if (k == 0)
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
	printf("ALLOCATE STRING\n\n");
	word->word = allocate_string(line, word, &quotes);
	if (!word->word)
		return (free_word(word), 1);
	if (quotes != NONE)
		return (free_word(word), free(line), ft_printf("ERREUR DE QUOTES\n")); // Changer le ft_printf par la fonction d'erreur, erreur de quotes !
	printf("STRLCPY\n\n");
	strlcpy(line, word, &quotes);
	printf("VALEUR DE i: %d\n", *i);
	if (!word->word)
		return (free_word(word), 1);								// Changer le return par la fonction d'erreur, erreur d'allocation !
	printf("Word: %s\n", word->word);
	free_word(word);
	return (0);
}
