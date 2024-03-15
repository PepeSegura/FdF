/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:55:12 by psegura-          #+#    #+#             */
/*   Updated: 2024/03/15 17:39:18 by psegura-         ###   ########.fr       */
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

void	rotate_by_z(int *x, int *y)
{
	const double	theta = -45.0 * (M_PI / 180);
	double			final_x;
	double			final_y;
	
	final_x = (cos(theta) * (*x)) + (-sin(theta) * (*y));
	final_y = (sin(theta) * (*x)) + (cos(theta) * (*y));
	(*x) = final_x;
	(*y) = final_y;
}

void	rotate_by_x(int *y, int *z)
{
	const double	theta = 30.0 * (M_PI / 180);
	double			final_y;
	double			final_z;
	
	final_y = (cos(theta) * (*y)) + (-sin(theta) * (*z));
	final_z = (sin(theta) * (*y)) + (cos(theta) * (*z));
	(*y) = final_y;
	(*z) = final_z;
}

void	rotate_by_y(int *x, int *z)
{
	const double	theta = 30.0 * (M_PI / 180);
	double			final_x;
	double			final_z;

	final_x = (cos(theta) * (*x)) + (sin(theta) * (*z));
	final_z = (-sin(theta) * (*x)) + (cos(theta) * (*z));
	(*x) = final_x;
	(*z) = final_z;
}

void	rotate_point(int *x, int *y, int *z)
{
	rotate_by_x(y, z);
	rotate_by_y(x, z);
	rotate_by_z(x, y);
}

// cos(θ)	-sin(θ)	0		X
// sin(θ)	 cos(θ)	0		Y
// 0			0	1		Z

// 1			0	0		X
// 0	 		0	0		Y
// 0			0	0		Z
