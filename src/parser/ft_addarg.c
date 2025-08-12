/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addarg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:34 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:12:35 by mavander         ###   ########.fr       */
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

t_bool	ft_addarg(t_shell *sh, t_cmd *tcmd)
{
	t_list	*new;
	t_arg	*content;

	content = argcontent(sh);
	if (!content)
		return (FALSE);
	if (content->name[0] == '\0')
		return (ft_free_targ(content), TRUE);
	new = ft_lstnew(content);
	if (!new)
		return (ft_free_targ(content), ft_seterror(sh, FTERR_ALLOC, 2), FALSE);
	ft_lstadd_back(&tcmd->arg, new);
	return (1);
}
