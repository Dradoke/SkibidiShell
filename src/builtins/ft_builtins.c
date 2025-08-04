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

int	ft_builtins(t_shell *sh, t_list **env, t_builtins *builtins)
{
	t_list	*args;
	int		idx0;

	args = ((t_cmd *)sh->cmd->content)->arg;
	idx0 = get_tabindex(hash_key(((t_arg *)args->content)->name));
	return (builtins[idx0].fn(sh, env));
}
