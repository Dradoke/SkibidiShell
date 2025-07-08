/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skibidi_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

/* FNV1 hashing function */
unsigned long	hash_key(const char *s)
{
	unsigned long	hash;
	int				i;

	if (!s)
		return (0);
	i = 0;
	hash = OFFSET;
	while (s[i])
	{
		hash ^= s[i++];
		hash *= PRIME;
	}
	return (hash);
}

int	get_tabindex(unsigned long hash)
{
	int	index;

	index = hash & (TABLE_SIZE - 1);
	return (index);
}

static void	add_builtins(t_builtins **builtins)
{
	int i;
	static char	*builtins_name[7] = {
	{"cd"},
	{"echo"},
	{"env"},
	{"exit"},
	{"export"},
	{"pwd"},
	{"unset"}
	};

	i = 0;
	while (i < 7)
	{
		
	}
	
}

t_builtins	*builtins_init(void)
{
	t_builtins	*builtins;

	builtins = ft_calloc(sizeof(t_builtins) * TABLE_SIZE);
	if (!builtins)
		return (NULL);
	add_builtins(builtins);
	return (builtins);
}
