/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:11:44 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:11:45 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

int	ft_builtins(t_shell *sh, t_cmd *cmd)
{
	t_list	*args;
	int		idx0;

	args = cmd->arg;
	idx0 = get_tabindex(hash_key(((t_arg *)args->content)->name));
	return (sh->bultins[idx0].fn(sh, &sh->env, cmd));
}
