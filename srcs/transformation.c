/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:55:12 by psegura-          #+#    #+#             */
/*   Updated: 2024/03/08 20:11:44 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	fast_sqrt(float x)
{
	float	xhalf;
	int		i;

	xhalf = 0.5f * x;
	i = *(int *)&x;
	i = 0x5f3759df - (i >> 1);
	x = *(float *)&i;
	x = x * (1.5f - (xhalf * x * x));
	x = x * (1.5f - (xhalf * x * x));
	x = 1 / x;
	return (x);
}

void	rotate_point(int *x, int *y, int *z)
{
	const double	theta = M_PI / 4.0;
	double			final_x;
	double			final_y;
	double			final_z;

	final_x = (cos(theta) * (*x)) + (-sin(theta) * (*y)) + (0 * (*z));
	final_y = (sin(theta) * (*x)) + (cos(theta) * (*y)) + (0 * (*z));
	final_z = (0 * (*x)) + (0 * (*y)) + (1 * (*z));
	(*x) = final_x;
	(*y) = final_y;
	(*z) = final_z;
}

// cos(θ)	-sin(θ)	0		X
// sin(θ)	 cos(θ)	0		Y
// 0			0	1		Z
