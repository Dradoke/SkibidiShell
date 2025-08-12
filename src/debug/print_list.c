/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:14 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:12:15 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

void	content_type_divider(t_lstype type)
{
	if (type == CMD)
		ft_printfd(1, "🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦\n");
	else if (type == REDIR)
		ft_printfd(1, "🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\n");
	else if (type == ARG)
		ft_printfd(1, "🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨\n");
}

void	print_redir(t_redir *redir)
{
	ft_printfd(1, "Name\t\t\t: %s\n", redir->name);
	ft_printfd(1, "FD\t\t\t: %i\n", redir->fd);
	if (redir->type == OUTFILE)
		ft_printfd(1, "Type\t\t\t: OUTFILE\n");
	else if (redir->type == INFILE)
		ft_printfd(1, "Type\t\t\t: INFILE\n");
	else if (redir->type == HEREDOC)
		ft_printfd(1, "Type\t\t\t: HEREDOC\n");
	else if (redir->type == APPEND)
		ft_printfd(1, "Type\t\t\t: APPEND\n");
}

void	print_tlist_info(t_list *lst)
{
	ft_printfd(1, "--------------Node #%i--------------\n", lst->index);
	ft_printfd(1, "Prev Node\t\t: %p\n", lst->prev);
	ft_printfd(1, "Node Addr\t\t: %p\n", lst);
	ft_printfd(1, "Content\t\t\t: %p\n", lst->content);
	ft_printfd(1, "Next Node\t\t: %p\n", lst->next);
	ft_printfd(1, "------------------------------------\n");
}

void	print_content(t_lstype type, t_list *lst)
{
	if (type == CMD)
	{
		ft_printfd(1, "Content Type\t\t: COMMAND (t_cmd)\n");
		print_list(((t_cmd *)lst->content)->redir, REDIR);
		print_list(((t_cmd *)lst->content)->arg, ARG);
		ft_printfd(1, "---------------------------------------Last Infile\n");
		if (((t_cmd *)lst->content)->last_redir[INPUT])
			print_redir(((t_cmd *)lst->content)->last_redir[INPUT]);
		ft_printfd(1, "--------------------------------------Last Outfile\n");
		if (((t_cmd *)lst->content)->last_redir[OUTFILE])
			print_redir(((t_cmd *)lst->content)->last_redir[OUTFILE]);
	}
	else if (type == REDIR)
	{
		ft_printfd(1, "Content Type\t\t: REDIRECTION (t_redir)\n");
		print_redir(lst->content);
	}
	else if (type == ARG)
	{
		ft_printfd(1, "Content Type\t\t: ARGUMENT (t_arg)\n");
		ft_printfd(1, "Arg Name\t\t: %s\n", ((t_arg *)lst->content)->name);
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
