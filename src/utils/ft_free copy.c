/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

bool	ft_free_list(t_list	*list, void (*f)(void *))
{
	if (!list || !f)
		return (1);
	f(list->content);
	while (list->next)
	{
		list = list->next;
		f(list->content);
		free(list->prev);
	}
	free(list);
	return (0);
}

static void	ft_free_content(void *content, t_lst_type type)
{
	if (!content)
		return ;
	if (type == REDIR)
	{
		free(((t_redir *)content)->name);
		free((t_redir *)content);
	}
	if (type == ARG)
	{
		free(((t_arg *)content)->name);
		free((t_arg *)content); 
	}
	if (type == CMD)
	{
		ft_free_list(((t_cmd *)content)->redir, ft_free_content(content, REDIR));
		ft_free_list(((t_cmd *)content)->arg, ft_free_content);
		free(((t_cmd *)content)->last_redir);
		free((t_cmd *)content);
	}
	if (type == ENV)
	{
		
	}
}
