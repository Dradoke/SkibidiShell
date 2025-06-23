/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

static void	ft_free_content(void *content, t_lstype type)
{
	if (!content)
		return ;
	if (type == REDIR)
		free(((t_redir *)content)->name);
	if (type == ARG)
		free(((t_arg *)content)->name);
	if (type == CMD)
	{
		ft_free_list(((t_cmd *)content)->redir, REDIR);
		ft_free_list(((t_cmd *)content)->arg, ARG);
	}
	if (type == ENV)
	{
		free(((t_env *)content)->key);
		free(((t_env *)content)->value);
	}
	free(content);
}

bool	ft_free_list(t_list	*list, t_lstype type)
{
	while (list)
	{
		ft_free_content(list->content, type);
		free(list->content);
		list = list->next;
		free(list->prev);
	}
	free(list);
	return (1);
}
