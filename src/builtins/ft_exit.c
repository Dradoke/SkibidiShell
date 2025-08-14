/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:11:59 by mavander          #+#    #+#             */
/*   Updated: 2025/08/14 14:54:38 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

int	normalize_exit_code(int ret_nb)
{
	if (ret_nb < 0)
		return (256 - (ret_nb * -1));
	return (ft_abs(ret_nb) & 0xFF);
}

void	close_stdfd(t_shell *sh)
{
	close(sh->std_fd[INPUT]);
	close(sh->std_fd[OUTPUT]);
}

int	ft_exit(t_shell *sh, t_list **env, t_cmd *cmd)
{
	t_list	*args;
	char	*arg_name;
	long	ret_nb;
	int		code;

	(void)env;
	if (!cmd->arg->next)
	{
		code = ft_atoi(sh->last_err);
		close_stdfd(sh);
		ft_free_all(&sh);
		ft_printfd(STDOUT_FILENO, "exit\n");
		return (exit(code), 1);
	}
	if (check_args_exit(sh, cmd) == 1)
		return (0);
	args = cmd->arg->next;
	arg_name = ((t_arg *)args->content)->name;
	ret_nb = ft_atol(arg_name);
	return (close_stdfd(sh), ft_free_all(&sh),
		exit(normalize_exit_code(ret_nb)), 0);
}
