/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpyword.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:40 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:12:41 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

static int	quote_verif(char c, t_quote *quote, size_t *i)
{
	if (c == '\"' && *quote == NONE)
		return (*quote = DOUBLE, (*i)++, 1);
	if (c == '\'' && *quote == NONE)
		return (*quote = SINGLE, (*i)++, 1);
	if ((c == '\"' && *quote == DOUBLE)
		|| (c == '\'' && *quote == SINGLE))
		return (*quote = NONE, (*i)++, 1);
	return (0);
}

static t_bool	writeword(t_shell *sh, char *dest)
{
	int		k;
	t_quote	quote;

	k = 0;
	quote = NONE;
	while (sh->line[sh->i]
		&& (quote
			|| (!ft_isdelim(sh->line[sh->i]) && !ft_isspace(sh->line[sh->i]))))
	{
		if (quote_verif(sh->line[sh->i], &quote, &sh->i))
			continue ;
		if (sh->line[sh->i] == '$' && quote != SINGLE)
		{
			sh->i++;
			ft_write_env(sh, &sh->line[sh->i], &dest[k], &sh->i);
			k += ft_strlen(&dest[k]);
			continue ;
		}
		else
			dest[k++] = sh->line[sh->i];
		sh->i++;
	}
	dest[k] = '\0';
	return (TRUE);
}

static char	*allocword(t_shell *sh, char *word)
{
	size_t	i;
	size_t	len;
	t_quote	quote;

	i = 0;
	len = 0;
	quote = NONE;
	while (word[i]
		&& (quote || (!ft_isdelim(word[i]) && !ft_isspace(word[i]))))
	{
		if (quote_verif(word[i], &quote, &i))
			continue ;
		if (quote == NONE && ft_isinvalidchar(word[i]))
			return (ft_seterror(sh, FTERR_SYNTAX, 2), NULL);
		else if (word[i] == '$' && quote != SINGLE)
			len += ft_get_env_size(sh, &word[i + 1], &i);
		else
			len++;
		i++;
	}
	if (quote != NONE)
		return (ft_seterror(sh, FTERR_QUOTE, 2), NULL);
	return (ft_calloc(len + 1));
}

char	*ft_cpyword(t_shell *sh)
{
	char	*word;

	ft_skipspace(sh->line, &sh->i);
	if (ft_isdelim(sh->line[sh->i]))
		return (ft_seterror(sh, FTERR_SYNTAX, 2), NULL);
	word = allocword(sh, &sh->line[sh->i]);
	if (!word)
		return (NULL);
	if (!writeword(sh, word))
		return (free(word), ft_seterror(sh, FTERR_ALLOC, 2), NULL);
	return (word);
}
