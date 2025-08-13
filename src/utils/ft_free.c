/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:13:07 by mavander          #+#    #+#             */
/*   Updated: 2025/08/13 18:08:38 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

void	ft_free_targ(void *targ)
{
	t_arg	*content;

	content = targ;
	if (!content)
		return ;
	if (content->name)
		free(content->name);
	free(content);
}

void	ft_free_tredir(void *tredir)
{
	t_redir	*content;

	content = tredir;
	if (!content)
		return ;
	if (content->name)
		free(content->name);
	if (content->hdoc_path)
		free(content->hdoc_path);
	free(content);
}

void	ft_free_tenv(void *tenv)
{
	t_env	*content;

	content = tenv;
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

	content = tcmd;
	if (!content)
		return ;
	ft_lstclear(&content->redir, ft_free_tredir);
	ft_lstclear(&content->arg, ft_free_targ);
	content->last_redir[INPUT] = NULL;
	content->last_redir[OUTPUT] = NULL;
	free(content);
}

void	ft_free_all(t_shell **sh)
{
	t_shell	*shc;

	shc = *sh;
	if (!shc)
		return ;
	ft_clearerror(*sh);
	if (shc->cmd)
		ft_lstclear(&shc->cmd, ft_free_tcmd);
	if (shc->env)
		ft_lstclear(&shc->env, ft_free_tenv);
	if (shc->bultins)
		ft_vfree(2, &shc->bultins->name, &shc->bultins);
	ft_vfree(2, &shc->line, &shc->last_err);
	free(shc);
}
