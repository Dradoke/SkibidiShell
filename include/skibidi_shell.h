/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skibidi_shell.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
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

extern volatile sig_atomic_t	g_signal_received;

/* builtins */

// hashing values
# define OFFSET 32
# define PRIME 23
// size of builtins's table 
# define TABLE_SIZE 16

#endif
