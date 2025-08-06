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
		return (FALSE);
	add_history(sh->line);
	sh->i = 0;
	if (!ft_parser(sh))
		return (FALSE);
	if (!ft_heredoc(sh, sh->cmd))
		return (FALSE);
	if (!ft_exec(sh))
		return (FALSE);
	return (TRUE);
}

static t_bool	loop_shell(t_shell *sh)
{
	free_shell(sh);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	sh->line = readline("SkibidiShell ➜ ");
	if (!sh->line)
		return (ft_printfd(STDOUT_FILENO, "Leaving SkibidiShell...\n"), FALSE);
	if (!process_line(sh))
		return (ft_puterror(sh), TRUE);
	return (ft_seterror(sh, "", 0), TRUE);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*sh;

	(void)ac;
	(void)av;
	sh = ft_calloc(sizeof(t_shell));
	if (!sh)
		return (1);
	sh->env = ft_env_to_lst(sh, env);
	sh->last_err = ft_itoa(0);
	sh->bultins = builtins_init();
	while (1)
		if (!loop_shell(sh))
			break ;
	ft_lstclear(&sh->env, ft_free_tenv);
	free(sh->last_err);
	free(sh->bultins);
	free(sh);
	clear_history();
	return (0);
}
