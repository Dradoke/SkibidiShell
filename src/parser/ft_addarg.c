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

static t_arg	*argcontent(t_shell *sh)
{
	t_arg	*targ;

	targ = ft_calloc(sizeof(t_arg));
	if (!targ)
		return (ft_seterror(sh, FTERR_ALLOC, 2), NULL);
	targ->name = ft_cpyword(sh);
	if (!targ->name)
		return (free(targ), NULL);
	return (targ);
}

bool	ft_addarg(t_shell *sh, t_cmd *tcmd)
{
	ft_lstadd_back(&tcmd->arg, ft_lstnew(argcontent(sh)));
	if (!ft_lstlast(tcmd->arg)->content)
		return (0);
	return (1);
}
