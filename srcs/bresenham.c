/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 03:11:32 by psegura-          #+#    #+#             */
/*   Updated: 2024/03/06 04:29:57 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_bresenham
{
	t_point	prev;
	t_point	new;
	int		delta_x;
	int		delta_y;
	int		step_x;
	int		step_y;
	int		err;
	int		x;
	int		y;
}			t_bresenham;

void	init_bresenham(t_bresenham *b, t_point prev, t_point new)
{
	b->prev = prev;
	b->new = new;
	b->delta_x = abs(new.x - prev.x);
	b->delta_y = abs(new.y - prev.y);
	b->step_x = -1;
	b->step_y = -1;
	if (b->prev.x < b->new.x)
		b->step_x = 1;
	if (b->prev.y < b->new.y)
		b->step_y = 1;
	b->err = b->delta_x - b->delta_y;
	b->x = b->prev.x;
	b->y = b->prev.y;
}

void	bresenham_line(t_data *img, t_point prev, t_point new)
{
	t_bresenham	b;
	int			e2;

	if ((new.x < 0 || new.x > SCREEN_WIDTH)
		|| (new.y < 0 || new.y > SCREEN_HEIGHT))
		return ;
	init_bresenham(&b, prev, new);
	while (b.x != new.x || b.y != new.y)
	{
		if ((b.x >= 0 && b.x < SCREEN_WIDTH)
			&& (b.y >= 0 && b.y < SCREEN_HEIGHT))
			my_mlx_pixel_put(img, b.x, b.y, new.color);
		e2 = 2 * b.err;
		if (e2 > -b.delta_y)
		{
			b.err -= b.delta_y;
			b.x += b.step_x;
		}
		if (e2 < b.delta_x)
		{
			b.err += b.delta_x;
			b.y += b.step_y;
		}
	}
}
