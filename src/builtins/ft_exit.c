/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:11:59 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:46:01 by mavander         ###   ########.fr       */
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

static void	handle_invalid_argument(char *arg_name)
{
	ft_printfd(STDERR_FILENO, FTERR_EXIT_NB, arg_name);
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
	int		ret_nb;
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
		handle_invalid_argument(arg_name);
	ret_nb = ft_atoi(arg_name);
	close_stdfd(sh);
	ft_free_all(&sh);
	exit(normalize_exit_code(ret_nb));
	return (0);
}
