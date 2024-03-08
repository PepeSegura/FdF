/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:41:36 by psegura-          #+#    #+#             */
/*   Updated: 2024/03/08 19:43:34 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_img(t_fdf *fdf)
{
	int	i;
	int j;

	i = 0;
	while (i < fdf->screen_width)
	{
		j = 0;
		while (j < fdf->screen_height)
		{
			my_mlx_pixel_put(&fdf->img, i, j, 0x0);
			j++;
		}
		i++;
	}
}

void draw_points(t_fdf *fdf, t_mlx *mlx)
{
	t_point **points = fdf->map.map;
	t_map	map = fdf->map;
	t_point	prev;
	t_point	new;

	clear_img(fdf);

	// Calculate the center of the map
	int map_center_x = map.height / 2;
	int map_center_y = map.wide / 2;

	double window_center_x = (fdf->screen_width / 2);
	double window_center_y = (fdf->screen_height / 2);

	printf("window size: (%4d,%4d)\n", fdf->screen_width, fdf->screen_height);

	//Draw horizontal lines
	for (int i = 0; i < map.height; i++)
	{
		for (int j = 0; j < map.wide; j++)
		{
			prev.x = new.x;
			prev.y = new.y;
			new.x = (window_center_x + (j - map_center_y) * fdf->zoom);
			new.y = (window_center_y + (i - map_center_x) * fdf->zoom);
			new.y -= points[i][j].height * fdf->scale;
			rotate_point(&new.x, &new.y, &points[i][j].height);
			new.x += fdf->translate_x;
			new.y += fdf->translate_y;
			new.color = points[i][j].color;
			if (j != 0)
				bresenham_line(fdf, prev, new);
		}
	}
	// Draw vertical lines
	for (int j = 0; j < map.wide; j++)
	{
		for (int i = 0; i < map.height; i++)
		{
			prev.x = new.x;
			prev.y = new.y;
			new.x = (window_center_x + (j - map_center_y) * fdf->zoom);
			new.y = (window_center_y + (i - map_center_x) * fdf->zoom);
			new.y -= points[i][j].height * fdf->scale;
			rotate_point(&new.x, &new.y, &points[i][j].height);
			new.x += fdf->translate_x;
			new.y += fdf->translate_y;
			new.color = points[i][j].color;
			if (i != 0)
				bresenham_line(fdf, prev, new);
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, fdf->img.img, 0, 0);
}