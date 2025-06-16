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

static void	free_word(t_word *word)
{
	if (word->j)
	{
		free(word->j);
		word->j = NULL;
	}
	if (word->word)
	{
		free(word->word);
		word->word = NULL;
	}
	if (word)
	{
		free(word);
		word = NULL;
	}
}

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
}

static char	*allocate_string(t_shell *sh, t_quotes_verif *quotes)
{
	int		j;
	char	*str;
	t_list	*start;

	j = 0;
	start = sh->env;
	while (sh->line[sh->i] && ((!ft_isdelim(sh->line[sh->i]) && !ft_isspace(sh->line[sh->i]))
			|| (*quotes) == SIMPLE || (*quotes) == DOUBLE))
	{
		if (quotes_usecase(sh->line[sh->i], quotes))
			quotes_verif(&sh->line[sh->i], quotes, false);
		else if (sh->line[sh->i] == '$')
		{
			ft_get_env_size(str, &sh->line[sh->i], (*quotes), &sh->i);
			sh->env = start;
		}
		else if (!ft_isspace(sh->line[sh->i]) || (*quotes != NONE))
			j++;
		sh->i++;
	}
	str = ft_calloc(sizeof(char) * (j + 1));
	return (str);
}

static void	strlcpy(char *line, t_word *word, t_quotes_verif *quotes)
{
	int	k;

	k = 0;
	while (line[(*word->i)] && ((!ft_isdelim(line[(*word->i)]) && !ft_isspace(line[(*word->i)]))
			|| (*quotes) == SIMPLE || (*quotes) == DOUBLE))
	{
		if (quotes_usecase(line[(*word->i)], quotes))
			quotes_verif(&line[(*word->i)++], quotes, true);
		else if (line[(*word->i)] == '$')
			ft_write_env(&line[(*word->i)], &k, word, quotes);
		else
			word->word[k++] = line[(*word->i)++];
	}
	if (ft_isdelim(line[(*word->i)]) && *word->j == 0)
		(*word->i)++;
	word->word[k] = '\0';
}

char	*ft_cpyword(t_shell *sh)
{
	t_quotes_verif	quotes;
	char			*str;

	quotes = NONE;
	ft_skipspace(sh->line, sh->i);
	str = allocate_string(sh->line, &quotes);
	if (!str)
		return (free_word(word), NULL);
	if (quotes != NONE)
		return (ft_printf("ERREUR DE QUOTES\n"), NULL);
	strlcpy(line, word, &quotes);
	if (!str)
		return (free_word(word), NULL);
	free_word(word);
	return (str);
}
