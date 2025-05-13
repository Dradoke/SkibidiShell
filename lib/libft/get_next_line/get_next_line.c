/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:05:27 by ngaudoui          #+#    #+#             */
/*   Updated: 2025/03/26 15:32:06 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Builds a line from a buffer until newline or EOF.
// Reads from fd, reallocates memory as needed, copies characters.
// Returns the complete line or NULL on error/EOF.
char	*make_line(char *buf, int fd, char **buff)
{
	t_gnl_vars	x;

	x.li = 0;
	x.llen = 1;
	x.line = NULL;
	while (1)
	{
		while (*buf)
		{
			x.llen += linelen(buf, x.nl);
			x.line = ft_realloc(x.line, x.llen);
			if (!x.line)
				return (free(buf), *buff = NULL, NULL);
			cpybuf(x.line, buf, &x.li);
			if (x.nl[1])
				return (x.line);
		}
		x.readb = read(fd, buf, BUFFER_SIZE);
		if (x.readb == 0 && x.line && x.line[0])
			return (free(buf), *buff = NULL, x.line);
		if (x.readb <= 0)
			return (free(buf), free(x.line), *buff = NULL, NULL);
	}
}

// Reads the next line from a file descriptor.
// Maintains static buffers for multiple file descriptors.
// Returns one line at a time or NULL on error/EOF.
char	*get_next_line(int fd)
{
	static char	*bufs[OPEN_MAX] = {NULL};

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!bufs[fd])
		bufs[fd] = ft_calloc_char(BUFFER_SIZE + 1);
	if (bufs[fd])
		return (make_line(bufs[fd], fd, &(bufs[fd])));
	return (NULL);
}
