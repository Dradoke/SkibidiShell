#ifndef STRUCT_H
# define STRUCT_H


//ENUMS

typedef enum e_redir_type {
    INFILE,        // <
    OUTFILE,       // >
    HEREDOC,       // << 
    APPEND,        // >>
} t_redir_type;


//STRUCTS

typedef struct s_redir
{
	unsigned char	name;
	int				fd;
	t_redir_type	type;
}	t_redir;

#endif