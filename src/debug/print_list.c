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

void	content_type_divider(t_lstype type)
{
	if (type == CMD)
		printf("🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦\n");
	else if (type == REDIR)
		printf("🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\n");
	else if (type == ARG)
		printf("🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨\n");
}

void	print_redir(t_redir *redir)
{
	printf("Name\t\t\t: %s\n", redir->name);
	printf("FD\t\t\t: %i\n", redir->fd);
	if (redir->type == OUTFILE)
		printf("Type\t\t\t: OUTFILE\n");
	else if (redir->type == INFILE)
		printf("Type\t\t\t: INFILE\n");
	else if (redir->type == HEREDOC)
		printf("Type\t\t\t: HEREDOC\n");
	else if (redir->type == APPEND)
		printf("Type\t\t\t: APPEND\n");
}

void	print_tlist_info(t_list *lst)
{
	printf("---------------------Node #%i---------------------\n", lst->index);
	printf("Prev Node\t\t: %p\n", lst->prev);
	printf("Node Addr\t\t: %p\n", lst);
	printf("Content\t\t\t: %p\n", lst->content);
	printf("Next Node\t\t: %p\n", lst->next);
	printf("--------------------------------------------------\n");
}

void	print_content(t_lstype type, t_list *lst)
{
	if (type == CMD)
	{
		printf("Content Type\t\t: COMMAND (t_cmd)\n");
		print_list(((t_cmd *)lst->content)->redir, REDIR);
		print_list(((t_cmd *)lst->content)->arg, ARG);
		printf("---------------------------------------Last Infile\n");
		if (((t_cmd *)lst->content)->last_redir[INPUT])
			print_redir(((t_cmd *)lst->content)->last_redir[INPUT]);
		printf("--------------------------------------Last Outfile\n");
		if (((t_cmd *)lst->content)->last_redir[OUTFILE])
			print_redir(((t_cmd *)lst->content)->last_redir[OUTFILE]);
	}
	else if (type == REDIR)
	{
		printf("Content Type\t\t: REDIRECTION (t_redir)\n");
		print_redir(lst->content);
	}
	else if (type == ARG)
	{
		printf("Content Type\t\t: ARGUMENT (t_arg)\n");
		printf("Arg Name\t\t: %s\n", ((t_arg *)lst->content)->name);
	}
}

void	print_list(t_list *lst, t_lstype type)
{
	while (lst)
	{
		content_type_divider(type);
		print_tlist_info(lst);
		if (lst->content)
			print_content(type, lst);
		lst = lst->next;
		content_type_divider(type);
	}
}
