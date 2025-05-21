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

static void free_word(t_word_info *word_info)
{
	if (word_info->j)
		free(word_info->j);
	if (word_info->word)
		free(word_info->word);
	// if (word_info)
		free(word_info);
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

static char	*allocate_string(char *line, t_word_info *word_info, t_quotes_verif	*quotes)
{
	int				i;
	char			*str;

	
	i = (*word_info->i);
	word_info->j = ft_calloc(sizeof(int) * 1);
	if (!word_info->j)
		return (NULL);
	while (line[i] && ((!ft_isdelim(line[i]) && !ft_isspace(line[i]))
			|| (*quotes) == SIMPLE || (*quotes) == DOUBLE))
	{
		if (line[i] == '\"' || line[i] == '\'')
			quotes_verif(&line[i], quotes);
		else if (!ft_isspace(line[i]) || (*quotes != NONE))
			(*word_info->j)++;
		printf("DEBUG: word_len = %d\n", (*word_info->j));
		i++;
	}
	str = ft_calloc(sizeof(char) * (*word_info->j + 1));
	if (!str)
		return (free_word(word_info), NULL);
	return (str);
}

static void	strlcpy(char *line, t_word_info *word_info)
{
	int	k;
	k = 0;
	if (*(word_info->j) > 0)
	{
		while (k < ((*word_info->j)))
		{
			if (line[(*word_info->i)] != '\0')
				word_info->word[k++] = line[(*word_info->i)];
			(*word_info->i)++;
		}
		word_info->word[k] = '\0';
	}
	(*word_info->i)++;
}

/*Copy a word until the next delimiter or space
  Return 0 if no error*/
bool	ft_cpyword(char *line, int *i)
{
	t_quotes_verif	quotes;
	t_word_info		*word_info;

	word_info = ft_calloc(sizeof(t_word_info) * 1);
	if (!word_info)
		return (1);
	quotes = NONE;
	word_info->i = i;
	while (line[*i] && ft_isspace(line[*i]))
	{
		(*i)++;
	}
	
	word_info->word = allocate_string(line, word_info, &quotes);
	if (!word_info->word)
		return (free_word(word_info), 1);
	strlcpy(line, word_info);
	if (!word_info->word)
		return (free_word(word_info), 1);								// Changer le return par la fonction d'erreur, erreur d'allocation !
	if (quotes != NONE)
		return (free_word(word_info), free(line), ft_printf("ERREUR DE QUOTES\n")); // Changer le ft_printf par la fonction d'erreur, erreur de quotes !
	printf("Word: %s\n", word_info->word);
	free_word(word_info);
	free(line);
	printf("VALEUR DE i: %d\n", *i);
	return (0);
}
