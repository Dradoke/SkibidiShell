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
#include <errno.h>

char	*skipspacestr(char *str)
{
	size_t	i;
	i = 0;
	ft_skipspace(str, &i);
	return (&str[i]);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*sh;

	sh = ft_calloc(sizeof(t_shell));
	sh->line = ft_strdup(av[1]);
	sh->env = ft_env_to_lst(env);
	ft_parser(sh);
	print_list(sh->cmd, CMD);
	(void)ac;
	(void)av;
	(void)env;
}
