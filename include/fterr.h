/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fterr.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:17:47 by mavander          #+#    #+#             */
/*   Updated: 2025/08/14 18:47:56 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTERR_H
# define FTERR_H
/* Generic */
# define FTERR_OPEN "Error: No such file or directory\n"
# define FTERR_PIPE "Error: Pipe failed\n"
# define FTERR_FORK "Error: Fork failed\n"

/* Parsing */
# define FTERR_REDIR "Error: Wrong redirection syntax\n"
# define FTERR_QUOTE "Error: Unclosed quote\n"
# define FTERR_INVALID_CHAR "Error: Invalid character outside quotes\n"
# define FTERR_SYNTAX "Error: Syntax\n"
# define FTERR_ALLOC "Error: Allocation failed\n"
# define FTERR_PARS_VAL 2

/*___________________________________________________________________________*/

/* Builtins */
# define FTERR_CD "Error: No such file or directory\n"
# define FTERR_ARGS "Error: too many arguments\n"
# define FTERR_NOTHOME "Error: HOME not set\n"
# define FTERR_CD_VAL 1

# define FTERR_ENV "Error: Empty list or failed allocation\n"
# define FTERR_ENV_VAL 2

# define FTERR_EXP "Error: not a valid identifier\n"
# define FTERR_EXP_VAL 2

# define FTERR_UNSET "Error: Invalid option\n"
# define FTERR_UNSET_VAL 2

# define FTERR_EXIT_NB "exit: %s: numeric argument required\n"
# define FTERR_EXIT_LONG "exit: numeric argument required\n"
# define FTERR_EXIT_ARG "exit: too many arguments\n"

/* Heredocs */
# define FTERR_HDOC_D "Warning: Heredoc delimited by EOF (wanted '%s')\n"

# define FTERR_PATH "Error: %s: No such file or directory\n"
# define FTERR_PATH_VAL 127

# define FTERR_ISDIR "Error: %s: Is a directory\n"
/* Exec */
# define FTERR_CMD "Error: %s: command not found\n"

# define FTERR_PERM "Error: %s: Permission denied\n"

#endif