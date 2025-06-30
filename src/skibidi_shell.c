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

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "skibidi_shell.h"

static void	free_shell(t_shell *sh)
{
	if (sh->line)
	{
		free(sh->line);
		sh->line = NULL;
	}
	if (sh->cmd)
		ft_lstclear(&sh->cmd, ft_free_tcmd);
}

static int	process_line(t_shell *sh)
{
	if (!sh->line || ft_strlen(sh->line) == 0)
		return (1);
	add_history(sh->line);
	sh->i = 0;
	if (!ft_parser(sh))
	{
		printf("SkibidiShell: parsing error\n");
		return (1);
	}
	print_list(sh->cmd, CMD);
	return (1);
}

void	sigint_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int ac, char **av, char **env)
{
	t_shell	*sh;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)ac;
	(void)av;
	sh = ft_calloc(sizeof(t_shell));
	if (!sh)
		return (1);
	sh->env = ft_env_to_lst(env);
	while (1)
	{
		free_shell(sh);
		sh->line = readline("SkibidiShell ➜ ");
		if (!sh->line)
		{
			printf("exit\n");
			break ;
		}
		process_line(sh);
	}
	ft_lstclear(&sh->env, ft_free_tenv);
	free(sh);
	clear_history();
	return (0);
}
