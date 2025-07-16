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

static void	free_shell(t_shell *sh)
{
	if (sh->line)
	{
		free(sh->line);
		sh->line = NULL;
	}
	if (sh->cmd)
		ft_lstclear(&sh->cmd, ft_free_tcmd);
	ft_clearerror(sh);
}

static int	process_line(t_shell *sh)
{
	if (ft_strlen(sh->line) == 0)
		return (false);
	add_history(sh->line);
	sh->i = 0;
	if (!ft_parser(sh))
		return (false);
	print_list(sh->cmd, CMD);
	return (true);
}

void	sigint_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	loop_shell(t_shell *sh)
{
	free_shell(sh);
	sh->line = readline("SkibidiShell ➜ ");
	if (!sh->line)
		return (ft_printf("Leaving SkibidiShell...\n"), 0);
	if (!process_line(sh))
		return (ft_puterror(sh), 1);
	return (1);
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
	sh->env = ft_env_to_lst(sh, env);
	while (1)
		if (!loop_shell(sh))
			break ;
	ft_lstclear(&sh->env, ft_free_tenv);
	free(sh);
	clear_history();
	return (0);
}
