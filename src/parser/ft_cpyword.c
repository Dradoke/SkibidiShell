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

static void	quote_verif(char c, t_quote *quote)
{
	if (c == '\"' && *quote == NONE)
		*quote = DOUBLE;
	else if (c == '\'' && *quote == NONE)
		*quote = SINGLE;
	else if ((c == '\"' && *quote == DOUBLE)
		|| (c == '\'' && *quote == SINGLE))
		*quote = NONE;
}

static int	writeword(t_shell *sh, char *word)
{
	int		k;
	t_quote	quote;

	k = 0;
	quote = NONE;
	while (sh->line[sh->i] && !(!quote && (ft_isdelim(sh->line[sh->i])
				|| ft_isspace(sh->line[sh->i]))))
	{
		quote_verif(sh->line[sh->i], &quote);
		if (sh->line[sh->i] == '$' && quote != SINGLE)
		{
			if (!ft_write_env(&sh->line[sh->i], &word[k], &sh->i, sh->env))
				return (0);
			k += ft_strlen(&word[k]);
			continue ;
		}
		else
			word[k++] = sh->line[sh->i];
		sh->i++;
	}
	word[k] = '\0';
	return (1);
}

static char	*allocword(t_shell *sh, char *word, t_list *env)
{
	size_t	i;
	size_t	len;
	t_quote	quote;

	i = 0;
	len = 0;
	quote = NONE;
	while (word[i] && !(!quote && (ft_isdelim(word[i])
				|| ft_isspace(word[i]))))
	{
		quote_verif(word[i], &quote);
		if (quote == NONE && ft_isinvalidchar(word[i]))
			return (ft_seterror(sh, FTERR_SYNTAX, 2), NULL);
		else if (word[i] == '$' && quote != SINGLE)
			len += ft_get_env_size(&word[i +1], &i, env);
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
	word = allocword(sh, &sh->line[sh->i], sh->env);
	if (!word)
		return (ft_seterror(sh, FTERR_ALLOC, 2), NULL);
	if (!writeword(sh, word))
		return (free(word), NULL);
	return (word);
}
