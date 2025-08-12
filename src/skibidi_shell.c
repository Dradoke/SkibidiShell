/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skibidi_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:13:25 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:19:07 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

volatile sig_atomic_t	g_signal_received;

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
<<<<<<< HEAD
		return (FALSE);
<<<<<<< HEAD
	if (!ft_exec(sh))
		return (FALSE);
=======
>>>>>>> cb494be (Tiens voila le fichier avec les modifs Nathan :))
	ft_builtins(sh, &sh->env, sh->bultins);
=======
		return (FALSE);
	if (!ft_exec(sh))
		return (FALSE);
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 61bd8ed (Fixing errors)
=======
	ft_builtins(sh, sh->cmd->content);
>>>>>>> 971f0f0 (builtins changed, now take the current cmd and are working (#30))
=======
>>>>>>> 5a65f51 (Fixed most errors, need to check tester results)
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
	return (TRUE);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*sh;

	g_signal_received = 0;
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
<<<<<<< HEAD
<<<<<<< HEAD
	ft_free_all(&sh);
=======
	ft_lstclear(&sh->env, ft_free_tenv);
	free(sh->last_err);
	free(sh->bultins);
	free(sh);
>>>>>>> d4afd8b (Tiens voila le fichier avec les modifs Nathan :))
=======
	ft_free_all(&sh);
>>>>>>> 40c5d05 (Fixed error codes in path, and leaks)
	clear_history();
	return (0);
}
