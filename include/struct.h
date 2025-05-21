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

typedef enum e_quotes_verif
{
	SIMPLE,		// '
	DOUBLE,		// "
	NONE
}	t_quotes_verif;

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

/* Structure utilitaire dans src/utils/ft_cpyword.c */
typedef struct	s_word_info
{
	int		*i;
	int		*j;
	int		k;
	char	*word;
	char	*env;
}	t_word_info;

#endif
