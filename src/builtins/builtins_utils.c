/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:11:41 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:11:42 by mavander         ###   ########.fr       */
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
	return (hash & (TABLE_SIZE - 1));
}

static void	insert_builtins(t_builtins *builtins)
{
	int					i;
	int					hash;
	int					idx0;
	static t_builtins	builtins_name[7] = {
	{"cd", ft_cd},
	{"echo", ft_echo},
	{"env", ft_env},
	{"exit", ft_exit},
	{"export", ft_export},
	{"pwd", ft_pwd},
	{"unset", ft_unset}
	};

	i = 0;
	hash = 0;
	idx0 = 0;
	while (i < 7)
	{
		hash = hash_key(builtins_name[i].name);
		idx0 = get_tabindex(hash);
		builtins[idx0].name = builtins_name[i].name;
		builtins[idx0].fn = builtins_name[i++].fn;
	}
}

t_bool	is_builtins(char *cmd, t_builtins *builtins)
{
	int		idx0;
	char	*builtin_name;

	idx0 = get_tabindex(hash_key(cmd));
	builtin_name = builtins[idx0].name;
	if (builtins[idx0].name)
	{
		if (ft_strncmp(cmd, builtin_name, ft_strlen(builtin_name)) == 0)
			return (TRUE);
	}
	return (FALSE);
}

t_builtins	*builtins_init(void)
{
	t_builtins	*builtins;

	builtins = ft_calloc(sizeof(t_builtins) * TABLE_SIZE);
	if (!builtins)
		return (NULL);
	insert_builtins(builtins);
	return (builtins);
}
