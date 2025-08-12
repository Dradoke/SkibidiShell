/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:05 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:12:06 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

int	ft_pwd(t_shell *sh, t_list **env, t_cmd *cmd)
{
	char	*curr_path;

	(void)sh;
	(void)cmd;
	curr_path = ft_getenv_val(*env, "PWD");
	if (curr_path != NULL)
	{
		ft_printfd(STDOUT_FILENO, curr_path);
		ft_printfd(STDOUT_FILENO, "\n");
	}
	return (0);
}
