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

//---ENUMS---//

typedef enum e_redir_type
{
	INFILE,		// <
	OUTFILE,	// >
	HEREDOC,	// << 
	APPEND,		// >>
}	t_redir_type;

enum
{
	INPUT,		// 0
	OUTPUT,		// 1
};

//---STRUCTS---//

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

/*Environment variable*/
typedef struct s_env
{
	char			*key;
	char			*value;
}	t_env;

#endif
