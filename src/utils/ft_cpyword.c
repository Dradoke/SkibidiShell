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

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s + len))
		len++;
	return (len);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	if (!n)
		return ;
	i = 0;
	str = s;
	while (i < n)
		*(str + i++) = '\0';
}

void	*ft_calloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		return (NULL);
	ft_bzero(res, size);
	return (res);
}

static void	ft_quotes_verif(char *c, t_quotes_verif *quotes)
{
	if ((*c) == '\"' && (*quotes) == NONE)
	{
		(*quotes) = DOUBLE;
		(*c) = ' ';
	}
	else if ((*c) == '\'' && (*quotes) == NONE)
	{
		(*quotes) = SIMPLE;
		(*c) = ' ';
	}
	else if ((((*c) == '\"' && (*quotes) == DOUBLE) || ((*c) == '\'' && (*quotes) == SIMPLE)))
	{
		(*quotes) = NONE;
		(*c) = ' ';
	}
}

static char	*allocate_string(char *line, int *j, t_quotes_verif	*quotes)
{
	int				i;
	char			*str;

	i = 0;
	while (line[i] && ((!ft_isdelim(line[i]) && !ft_isspace(line[i])) || (*quotes) == SIMPLE || (*quotes) == DOUBLE))
			{
				if (line[i] == '\"' || line[i] == '\'')
					ft_quotes_verif(&line[i], quotes);
				printf ("i: %d, char: %c\n", i, line[i]);
				i++;
			}
	str = ft_calloc(sizeof(char) * i);
	if (!str)
		return (NULL);
	(*j) = i;
	return (str);
}

/*Copy a word until the next delimiter or space*/
bool	ft_cpyword(char *line, int *i)
{
	int	j;
	int	k;
	t_quotes_verif	quotes;
	char	*str;

	quotes = NONE;
	k = 0;
	str = allocate_string(line, &j, &quotes);
	if (!str)
		return (1);
	if (quotes != NONE)
		return (printf("ERREUR DE QUOTES"));
	if (j > 0)
	{
		printf("j: %d\n", j);
		while (line[(*i)] && (*i) < (j))
		{
			if (!ft_isspace(line[(*i)]))
				str[k++] = line[(*i)];
			(*i)++;
		}
		str[(*i)] = '\0';
	}
	(*i) += j;
	printf("%s", str);
	return (0);
}
