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
/* Generic */
# define FTERR_OPEN "Error: Open failed"
# define FTERR_PIPE "Error: Pipe failed"
# define FTERR_FORK "Error: Fork failed"

/* Parsing */
# define FTERR_REDIR "Error: Wrong redirection syntax"
# define FTERR_QUOTE "Error: Unclosed quote"
# define FTERR_INVALID_CHAR "Error: Invalid character outside quotes"
# define FTERR_SYNTAX "Error: Syntax"
# define FTERR_ALLOC "Error: Allocation failed"
# define FTERR_PARS_VAL 2

/*___________________________________________________________________________*/

/* Builtins */
# define FTERR_CD " No such file or directory\n"
# define FTERR_ARGS " too many arguments"
# define FTERR_CD_VAL 1

# define FTERR_ENV "Empty list or failed allocation\n"
# define FTERR_ENV_VAL 2

# define FTERR_EXP " not a valid identifier\n"
# define FTERR_EXP_VAL 2

# define FTERR_UNSET "Invalid option\n"
# define FTERR_UNSET_VAL 2

# define FTERR_EXIT_NB "exit\nexit: %s: numeric argument required\n"
# define FTERR_EXIT_ARG "exit\ntoo many arguments\n"

/* Heredocs */
# define FTERR_HDOC_D "Warning: Heredoc delimited by end-of-file (wanted '%s')\n"

# define FTERR_PATH "No such file or directory\n"
# define FTERR_PATH_VAL 127

/* Exec */
# define FTERR_CMD "Command doesn't exist\n"

#endif