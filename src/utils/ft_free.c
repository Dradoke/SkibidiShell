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

static void	ft_free_redir(void *content)
{
	if (!content)
		return ;
	free(((t_redir *)content)->name);
	free((t_redir *)content);
}

static void	ft_free_arg(void *content)
{
	if (!content)
		return ;
	free(((t_arg *)content)->name);
	free((t_arg *)content);
}

void	ft_free_cmd(void *content)
{
	if (!content)
		return ;
	ft_free_list(((t_cmd *)content)->redir, ft_free_redir);
	ft_free_list(((t_cmd *)content)->arg, ft_free_arg);
	free(((t_cmd *)content)->last_redir);
	free((t_cmd *)content);
}
