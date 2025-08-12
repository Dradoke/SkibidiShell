/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:12:57 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:12:58 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidi_shell.h"

int	ft_isinvalidchar(int c)
{
	if (c == ';' || c == '&' || c == '(' || c == ')'
		|| c == '\\' || c == '*' || c == '?'
		|| c == '[' || c == ']' || c == '{' || c == '}')
		return (1);
	return (0);
}

void	ft_seterror(t_shell *sh, char *msg, int code)
{
	sh->err.b = 1;
	if (sh->err.msg)
		free(sh->err.msg);
	sh->err.msg = ft_strdup(msg);
	sh->err.code = code;
	if (sh->last_err)
		free(sh->last_err);
	sh->last_err = ft_itoa(sh->err.code);
}

void	ft_clearerror(t_shell *sh)
{
	if (sh->err.msg)
	{
		free(sh->err.msg);
		sh->err.msg = NULL;
	}
	sh->err.b = 0;
	sh->err.code = 0;
}

int	ft_puterror(t_shell *sh)
{
	if (sh->err.b)
	{
		ft_printfd(STDERR_FILENO, "SkibidiERROR: %s", sh->err.msg);
		ft_clearerror(sh);
		return (ft_atoi(sh->last_err));
	}
	return (0);
}
