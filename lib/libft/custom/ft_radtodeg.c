/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_radtodeg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavander <mavander@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:42:42 by mavander          #+#    #+#             */
/*   Updated: 2025/08/12 21:13:57 by mavander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Converts radians to degrees.
// Multiplies radians by 180/pi for the conversion.
// Uses 3.14159265358979323846 as the value of pi.
float	ft_radtodeg(float rad)
{
	float		pi;
	float		deg;

	pi = 3.14159265358979323846f;
	deg = rad * (180.0f / pi);
	return (deg);
}
