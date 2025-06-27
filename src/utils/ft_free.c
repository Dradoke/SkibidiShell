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

void	ft_free_targ(void *targ)
{
	t_arg	*content;

	content = (t_arg *)targ;
	if (!content)
		return ;
	if (content->name)
		free(content->name);
	free(content);
}

void	ft_free_tredir(void *tredir)
{
	t_redir	*content;

	content = (t_redir *)tredir;
	if (!content)
		return ;
	if (content->name)
		free(content->name);
	free(content);
}

void	ft_free_tenv(void *tenv)
{
	t_env	*content;

	content = (t_env *)tenv;
	if (!content)
		return ;
	if (content->key)
		free(content->key);
	if (content->value)
		free(content->value);
	free(content);
}

void	ft_free_tcmd(void *tcmd)
{
	t_cmd	*content;

	content = (t_cmd *)tcmd;
	if (!content)
		return ;
	ft_lstclear(&content->redir, ft_free_tredir);
	ft_lstclear(&content->arg, ft_free_targ);
	content->last_redir[INPUT] = NULL;
	content->last_redir[OUTPUT] = NULL;
	free(content);
}
