/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:06:02 by ngaudoui          #+#    #+#             */
/*   Updated: 2025/08/12 21:15:31 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef OPEN_MAX
#  define OPEN_MAX 4096
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_all
{
	size_t	li;
	size_t	llen;
	char	*line;
	int		readb;
	int		nl[2];
}	t_gnl_vars;

char	*get_next_line(int fd);
char	*make_line(char *buf, int fd, char **buff);

int		linelen(char *str, int *nl);
void	cpybuf(char *line, char *buf, size_t *li);
char	*ft_calloc_char(size_t size);
char	*ft_realloc(char *s1, size_t size);

#endif