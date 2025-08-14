/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:17:55 by mavander          #+#    #+#             */
/*   Updated: 2025/08/14 13:34:22 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "skibidi_shell.h"

/*████████████████████████████████████████████████████████████████████████████*/

//---ENUMS---//
typedef enum e_redir_type
{
	INFILE,		// <
	OUTFILE,	// >
	HEREDOC,	// << 
	APPEND,		// >>
	NOT_REDIR,
}	t_redir_type;

typedef enum e_lstype
{
	CMD,
	REDIR,
	ARG,
	ENV,
}	t_lstype;

enum
{
	INPUT,		// 0
	OUTPUT,		// 1
};

typedef enum e_bool
{
	FALSE,		// 0
	TRUE,		// 1
}	t_bool;

typedef enum e_quote
{
	NONE,
	SINGLE,		// '
	DOUBLE,		// "
}	t_quote;

typedef enum e_builtin_type
{
	CRITICAL,
	NEUTRAL,
}	t_builtin_type;

/*████████████████████████████████████████████████████████████████████████████*/

//---STRUCTS---//
typedef struct s_err
{
	t_bool	b;
	int		code;
	char	*msg;
}	t_err;

typedef struct s_builtins	t_builtins;

typedef struct s_shell
{
	size_t		i;
	t_list		*cmd;
	t_list		*env;
	char		*line;
	t_err		err;
	char		*last_err;
	t_builtins	*bultins;
	int			pipe_old[2];
	int			pipe_new[2];
	int			std_fd[2];
}	t_shell;

typedef struct s_redir
{
	char			*name;
	char			*hdoc_path;
	int				fd;
	t_redir_type	type;
}	t_redir;

typedef struct s_arg
{
	char			*name;
}	t_arg;

typedef struct s_cmd
{
	t_list			*redir;
	t_list			*arg;
	t_redir			*last_redir[2];
	int				pid;
}	t_cmd;

// Environment Variable
typedef struct s_env
{
	char			*key;
	char			*value;
}	t_env;

typedef struct s_builtins
{
	char	*name;
	int		(*fn)(t_shell *sh, t_list **env, t_cmd *cmd);
}	t_builtins;

#endif
