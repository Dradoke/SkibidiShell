/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fterr.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTERR_H
# define FTERR_H

/* Parsing */
# define FTERR_REDIR "Error: Wrong redirection syntax"
# define FTERR_QUOTE "Error: Unclosed quote"
# define FTERR_INVALID_CHAR "Error: Invalid character outside quotes"
# define FTERR_SYNTAX "Error: Syntax"
# define FTERR_ALLOC "Error: Allocation failed"
# define FTERR_PARS_VAL 2

/*___________________________________________________________________________*/

/* Builtins */
# define FTERR_CD "Error: Path required"
# define FTERR_CD_VAL 1

# define FTERR_ENV "Error: Empty list or failed allocation"
# define FTERR_ENV_VAL 2

# define FTERR_EXP "Error: Not a valid identifier"
# define FTERR_EXP_VAL 2

# define FTERR_UNSET "Error: Invalid option"
# define FTERR_UNSET_VAL 2

# define FTERR_EXIT_NB "exit: %s: numeric argument required\n"
# define FTERR_EXIT_ARG "exit\nError: too many arguments"

# define FTERR_HDOC_D "Warning: Heredoc delimited by end-of-file (wanted '%s')"

#endif