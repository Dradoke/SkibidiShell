/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:06:36 by ngaudoui          #+#    #+#             */
/*   Updated: 2025/03/26 15:32:15 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Allocates and zero-initializes a character array.
// Allocates 'size' bytes of memory and fills them with null bytes.
// Returns a pointer to the allocated memory or NULL if allocation fails.
char	*ft_calloc_char(size_t size)
{
	char	*new;
	size_t	i;

	i = 0;
	new = malloc(size);
	if (!new)
		return (NULL);
	while (i < size)
		new[i++] = '\0';
	return (new);
}

// Reallocates a string to a new size.
// Copies content from 's1' to a new string of 'size' bytes.
// Returns a pointer to the new string or NULL if allocation fails.
char	*ft_realloc(char *s1, size_t size)
{
	char	*s2;
	size_t	i;

	i = 0;
	if (!s1)
		return (ft_calloc_char(size));
	s2 = ft_calloc_char(size);
	if (!s2)
		return (free(s1), NULL);
	while (s1[i] && i < size - 1)
	{
		s2[i] = s1[i];
		i++;
	}
	free(s1);
	return (s2);
}

// Calculates length of a line and checks for newline character.
// Stores position of newline in nl[0] and sets nl[1] if newline was found.
// Returns the number of characters to read until newline or end of string.
int	linelen(char *str, int *nl)
{
	nl[0] = 0;
	nl[1] = 0;
	while (str[nl[0]])
	{
		if (str[nl[0]] == '\n')
			return (nl[1] = 1, ++nl[0]);
		nl[0]++;
	}
	return (nl[0]);
}

// Copies characters from buffer to line and shifts remaining buffer content.
// Copies until newline or end of buffer, then shifts remaining characters.
// Updates line index and zeroes out used buffer positions.
void	cpybuf(char *line, char *buf, size_t *li)
{
	int	bj;
	int	bi;

	bj = 0;
	bi = 0;
	while (buf[bj])
	{
		if (buf[bj] == '\n')
		{
			line[(*li)++] = buf[bj++];
			break ;
		}
		line[(*li)++] = buf[bj++];
	}
	while (buf[bj])
		buf[bi++] = buf[bj++];
	while (bi < bj)
		buf[bi++] = '\0';
}
