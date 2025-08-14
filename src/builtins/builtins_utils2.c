/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:50:54 by ngaudoui          #+#    #+#             */
/*   Updated: 2025/08/14 19:34:49 by mavander         ###   ########.fr       */
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

static void	handle_invalid_argument(t_shell *sh, char *arg_name)
{
	(void)sh;
	ft_printfd(STDERR_FILENO, FTERR_EXIT_NB, arg_name);
	close_stdfd(sh);
	ft_free_all(&sh);
	exit (2);
}

int	check_args_exit(t_shell *sh, t_cmd *cmd)
{
	t_list	*args;
	char	*arg_name;
	long	ret_nb;
	t_bool	first_is_nb;

	args = cmd->arg->next;
	first_is_nb = FALSE;
	arg_name = ((t_arg *)args->content)->name;
	if (is_valid_number(arg_name))
		first_is_nb = TRUE;
	if (args->next && first_is_nb == TRUE)
		return (ft_printfd(STDERR_FILENO, FTERR_EXIT_ARG), 1);
	if (!first_is_nb)
		return (handle_invalid_argument(sh, arg_name), 2);
	ret_nb = ft_atol(arg_name);
	if (ret_nb > INT_MAX)
		return (ft_printfd(STDERR_FILENO, FTERR_EXIT_LONG), 1);
	return (0);
}
