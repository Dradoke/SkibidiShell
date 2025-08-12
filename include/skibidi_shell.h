/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skibidi_shell.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:17:53 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:18:03 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKIBIDI_SHELL_H
# define SKIBIDI_SHELL_H
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <wait.h>
# include <sys/stat.h>

# include "libft.h"

# include "struct.h"
# include "prototype.h"
# include "fterr.h"

/* builtins */

// hashing values
# define OFFSET 32
# define PRIME 23
// size of builtins's table 
# define TABLE_SIZE 16

#endif
