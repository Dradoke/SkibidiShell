/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addredir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

// DONE
static t_arg	*argcontent(t_shell *sh)
{
	t_arg	*targ;

	targ = ft_calloc(sizeof(t_arg));
	targ->name = ft_cpyword(sh->line, &sh->i, sh->env);
	return (targ);
}

// UN-FINISHED
void	ft_addarg(t_shell *sh, t_cmd *tcmd)
{
	ft_lstadd_back(&tcmd->arg, ft_lstnew(argcontent(sh)));
}
