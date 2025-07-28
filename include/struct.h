/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SkibidiShell - ngaudoui & mavander         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by SkibidiShell      #+#    #+#             */
/*   Updated: 2024/12/21 21:42:42 by SkibidiShell     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "skibidi_shell.h"

//---ENUMS---//
typedef enum e_redir_type
{
	INFILE,		// <
	OUTFILE,	// >
	HEREDOC,	// << 
	APPEND,		// >>
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

typedef enum e_quote
{
	NONE,
	SINGLE,		// '
	DOUBLE,		// "
}	t_quote;

//---STRUCTS---//

typedef struct s_err
{
	bool	b;
	int		code;
	char	*msg;
}	t_err;

typedef struct s_shell
{
	size_t	i;
	t_list	*cmd;
	t_list	*env;
	char	*line;
	t_err	err;
	char	*last_err;
}	t_shell;

typedef struct s_env
{
	char			*key;
	char			*value;
}	t_env;

typedef struct s_redir
{
	char			*name;
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
}	t_cmd;

#endif
