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

void	print_list(t_list *lst, t_lstype type)
{
	while (lst)
	{
		if (type == CMD)
			printf("🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦\n");
		else if (type == REDIR)
			printf("🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\n");
		else if (type == ARG)
			printf("🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨\n");
		printf("---------------------Node #%i---------------------\n", lst->index);
		printf("Prev Node\t\t: %p\n", lst->prev);
		printf("Node Addr\t\t: %p\n", lst);
		printf("Content\t\t\t: %p\n", lst->content);
		printf("Next Node\t\t: %p\n", lst->next);
		printf("--------------------------------------------------\n");
		if (type == CMD)
		{
			printf("Content Type\t\t: COMMAND (t_cmd)\n");
			print_list(((t_cmd *)lst->content)->redir, REDIR);
			print_list(((t_cmd *)lst->content)->arg, ARG);
			printf("---------------------------------------Last Infile\n");
			print_redir(((t_cmd *)lst->content)->last_redir[INPUT]);
			printf("--------------------------------------Last Outfile\n");
			print_redir(((t_cmd *)lst->content)->last_redir[OUTFILE]);
		}
		else if (type == REDIR)
		{
			printf("Content Type\t\t: REDIRECTION (t_redir)\n");
			print_redir(lst->content);
			print_list(lst->next, REDIR);
		}
		else if (type == ARG)
		{
			printf("Content Type\t\t: ARGUMENT (t_arg)\n");
			printf("Arg Name\t\t: %s\n", ((t_arg *)lst->content)->name);
			print_list(lst->next, ARG);
		}
		lst = lst->next;
		if (type == CMD)
			printf("🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦🟦\n");
		else if (type == REDIR)
			printf("🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩\n");
		else if (type == ARG)
			printf("🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨🟨\n");
	}
}

int	main(int ac, char **av, char **env)
{
	t_list	*cmd;

	cmd = (t_list *)ft_calloc(sizeof(t_list));

	cmd->content = ft_calloc(sizeof(t_cmd));

	((t_cmd *)cmd->content)->redir = ft_calloc(sizeof(t_list));
	((t_cmd *)cmd->content)->arg = ft_calloc(sizeof(t_list));
	((t_cmd *)cmd->content)->last_redir[0] = ft_calloc(sizeof(t_redir *));
	((t_cmd *)cmd->content)->last_redir[1] = ft_calloc(sizeof(t_redir *));

	((t_cmd *)cmd->content)->redir->content = ft_calloc(sizeof(t_redir));
	((t_cmd *)cmd->content)->arg->content = ft_calloc(sizeof(t_arg));

	((t_redir *)((t_cmd *)cmd->content)->redir->content)->name = ft_calloc(sizeof(char));
	((t_arg *)((t_cmd *)cmd->content)->arg->content)->name = ft_calloc(sizeof(char));
	
	ft_lstadd_back(&cmd, ft_lstnew(cmd->content));

	((t_redir *)((t_cmd *)cmd->content)->redir->content)->type = OUTFILE;
	print_list(cmd, CMD);
	(void)ac;
	(void)av;
	(void)env;
}