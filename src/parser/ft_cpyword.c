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
// FIXED
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

static void	writeword(t_shell *sh, char *word)
{
	int		k;
	t_quote	quote;

	k = 0;
	while (sh->line[(sh->i)] && ((!ft_isdelim(sh->line[(sh->i)]) && !ft_isspace(sh->line[(sh->i)]))
			|| (*quote) == SINGLE || (*quote) == DOUBLE))
	{
		if (word[sh->i] == '\"' || word[sh->i] == '\'')
			quote_verif(word[sh->i], &quote);
		else if (sh->line[sh->i] == '$')
			ft_write_env(&sh->line[sh->i], &k, word, quote);
		else
			word[k++] = sh->line[(sh->i)++];
	}
	if (ft_isdelim(sh->line[sh->i]) && k == 0)
		(sh->i)++;
	word[k] = '\0';
}
// Fixed
static char	*allocword(char	*word, t_list *env)
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
		if (word[i] == '\"' || word[i] == '\'')
			quote_verif(word[i], &quote);
		else if (word[i] == '$' && quote != SINGLE)
		{
			len += ft_get_env_size(word, &i, env, quote);
			continue ;
		}
		else
			len++;
		i++;
	}
	return (ft_calloc(len + 1));
}

char	*ft_cpyword(t_shell *sh)
{
	char	*word;

	word = allocword(sh->line, sh->env);
	if (!word)
		return (NULL);
	writeword(sh, word);
	return (word);
}
