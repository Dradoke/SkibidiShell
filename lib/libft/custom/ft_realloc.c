/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:14:05 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *original, size_t size)
{
	size_t	i;
	char	*src;
	char	*dest;

	src = original;
	if (!src)
		return (ft_calloc(size));
	i = 0;
	dest = ft_calloc(size);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	free(src);
	return (dest);
}
