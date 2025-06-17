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
		*quote = SIMPLE;
	else if ((c == '\"' && *quote == DOUBLE)
		|| (c == '\'' && *quote == SIMPLE))
		*quote = NONE;
}

static char	*allocword(t_shell *sh, t_quote *quote)
{
	int		len;
	char	*str;
	t_list	*start;

	len = 0;
	start = sh->env;
	while (sh->line[sh->i] && ((!ft_isdelim(sh->line[sh->i]) && !ft_isspace(sh->line[sh->i]))
			|| (*quote) == SIMPLE || (*quote) == DOUBLE))
	{
		if (quotes_usecase(sh->line[sh->i], quote))
			quotes_verif(&sh->line[sh->i], quote, false);
		else if (sh->line[sh->i] == '$')
		{
			ft_get_env_size(str, &sh->line[sh->i], (*quote), &sh->i);
			sh->env = start;
		}
		else if (!ft_isspace(sh->line[sh->i]) || (*quote != NONE))
			len++;
		sh->i++;
	}
	str = ft_calloc(sizeof(char) * (len + 1));
	return (str);
}

static void	writeword(t_shell *sh, char *word, t_quote *quote)
{
	int	k;

	k = 0;
	while (sh->line[(sh->i)] && ((!ft_isdelim(sh->line[(sh->i)]) && !ft_isspace(sh->line[(sh->i)]))
			|| (*quote) == SIMPLE || (*quote) == DOUBLE))
	{
		if (quotes_usecase(sh->line[sh->i], quote))
			quotes_verif(&sh->line[(sh->i)++], quote, true);
		else if (sh->line[sh->i] == '$')
			ft_write_env(&sh->line[sh->i], &k, word, quote);
		else
			word[k++] = sh->line[(sh->i)++];
	}
	if (ft_isdelim(sh->line[sh->i]) && k == 0)
		(sh->i)++;
	word[k] = '\0';
}

char	*ft_cpyword(t_shell *sh)
{
	char	*word;

	word = allocword(sh);
	if (!word)
		return (NULL);
	writeword(sh, word, &quote);
	return (word);
}

static char	*allocword(t_shell *sh)
{
	size_t	len;
	t_quote	quote;

	len = 0;
	while (sh->line[sh->i] && !(!quote && (ft_isdelim(sh->line[sh->i])
				|| ft_isspace(sh->line[sh->i]))))
	{
		quote_verif(sh->line[sh->i], &quote);
		if (sh->line[sh->i] == '$')
			len += ft_get_env_size(sh->line, sh->env, quote);
		len++;
		sh->i++;
	}
	return (ft_calloc(len + 1));
}
