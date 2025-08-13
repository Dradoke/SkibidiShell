/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:11:59 by mavander          #+#    #+#             */
/*   Updated: 2025/08/13 19:55:17 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

static t_bool	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (FALSE);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (FALSE);
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	normalize_exit_code(int ret_nb)
{
	if (ret_nb < 0)
		return (256 - (ret_nb * -1));
	return (ft_abs(ret_nb) & 0xFF);
}

static void	handle_invalid_argument(t_shell *sh, char *arg_name)
{
	ft_printfd(STDERR_FILENO, "exit\n"FTERR_EXIT_NB, arg_name);
	ft_free_all(&sh);
	exit(2);
}

static void	close_stdfd(t_shell *sh)
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
		exit(code);
	}
	args = cmd->arg->next;
	if (args->next)
		return (ft_printfd(STDERR_FILENO, FTERR_EXIT_ARG), 1);
	arg_name = ((t_arg *)args->content)->name;
	if (!is_valid_number(arg_name))
		handle_invalid_argument(sh, arg_name);
	ret_nb = ft_atol(arg_name);
	if (ret_nb > INT_MAX)
		return (ft_printfd(STDERR_FILENO, FTERR_EXIT_LONG), close_stdfd(sh),
			close_all_fd(cmd->redir),ft_free_all(&sh), exit(2), 1);
	return (close_stdfd(sh), ft_free_all(&sh),
		exit(normalize_exit_code(ret_nb)), 0);
}
