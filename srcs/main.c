/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:19:58 by psegura-          #+#    #+#             */
/*   Updated: 2024/02/24 18:01:52 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_input(int keycode, t_mlx *mlx)
{
	(void)mlx;
	if (keycode == ESC)
		exit (0);
	return (0);
}

void	exit_program(t_point **map)
{
	ft_free_matrix((char **)map);
	exit (0);
}

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	get_color(char *color)
{
	int	final_color;

	final_color = 0x00FFFFFF;
	if (color)
		final_color = (int)ft_atol_16(color);
	return (final_color);
}

void	draw_cross(t_data *img)
{
	const int	height_center = SCREEN_WIDTH / 2;
	const int	wide_center = SCREEN_HEIGHT / 2;

	printf("center (%d,%d)\n", height_center, wide_center);
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		my_mlx_pixel_put(img, i , wide_center, 0x0Fa3a3a3);
	}
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		my_mlx_pixel_put(img, height_center , i, 0x0Fa3a3a3);
	}
}

void	bresenham_line(t_data *img, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	x;
	int	y;
	int	e2;

	// printf("act: (%d, %d) old: (%d,%d)\n", x0, y0, x1, y1);
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1;
	err = dx - dy;
	x = x0;
	y = y0;
	while (x != x1 || y != y1)
	{
		printf("(%d, %d)\n", x, y);
		my_mlx_pixel_put(img, x, y, color);
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}

void draw_points(t_map *map, t_mlx *mlx)
{
	t_data img;
	t_point **points = map->map;

	img.img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	// Calculate the center of the map
	int map_center_x = map->height / 2;
	int map_center_y = map->wide / 2;

	double window_center_x = (SCREEN_WIDTH / 2);
	double window_center_y = (SCREEN_HEIGHT / 2);

	// Calculate the multiplier based on the size of the window and the map
	double multiplier_x = ((double)SCREEN_WIDTH / (double)map->height) / SCALE;
	double multiplier_y = ((double)SCREEN_HEIGHT / (double)map->wide) / SCALE;
	printf("mu XXX multii: %f\n", multiplier_x);
	printf("mu YYY multii: %f\n", multiplier_y);

	draw_cross(&img);
	printf("window size: (%4d,%4d)\n", SCREEN_WIDTH, SCREEN_HEIGHT);
	int x_draw = 0;
	int y_draw = 0;
	int x_prev = 0;
	int y_prev = 0;
	int color = 0;
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->wide; j++)
		{
			// Calculate the offset from the center of the map to the center of the window
			x_prev = x_draw;
			y_prev = y_draw;
			int x_offset = (j - map_center_y) * multiplier_x;
			int y_offset = (i - map_center_x) * multiplier_y;

			// Calculate the coordinates to draw the point
			x_draw = window_center_x + x_offset;
			y_draw = window_center_y + y_offset;
			// Draw the point
			printf("(%4d,%4d ) ", x_draw, y_draw);
			color = get_color(points[i][j].color);
			if (x_draw >= 0 && y_draw >= 0)
				my_mlx_pixel_put(&img, x_draw, y_draw, color);
			if (j != 0)
				bresenham_line(&img, x_prev, y_prev, x_draw, y_draw, color);
		}
		printf("\n");
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, 0, 0);
}

void	init_data(t_map *map, char *input_file)
{
	ft_memset(map, 0, sizeof(t_map));
	create_map_matrix(map, input_file);
	printf("map height: [%d] map wide: [%d] map pointer: [%p]\n",
		map->height, map->wide, map->map);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_mlx	mlx;

	if (argc != 2)
		exit(EXIT_FAILURE);
	
	init_data(&map, argv[1]);

	printf("map_loaded\n");
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "FDF");

	draw_points(&map, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, ft_input, &mlx);
	mlx_hook(mlx.win, 17, 0, ft_input, &mlx);

	mlx_loop(mlx.mlx);

	exit_program(map.map);
	return (0);
}
