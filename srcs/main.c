/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: SPACE24/02/10 SPACE:19:58 by psegura-          #+#    #+#             */
/*   Updated: SPACE24/02/24 21:55:24 by psegura-         ###   ########.fr       */
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
	const int	delta_x = abs(x1 - x0);
	const int	delta_y = abs(y1 - y0);
	int			step_x;
	int			step_y;
	int			err;
	int			x;
	int			y;
	int			e2;

	// printf("act: (%d, %d) old: (%d,%d)\n", x0, y0, x1, y1);
	if ((x1 < 0 || x1 > SCREEN_WIDTH) || (y1 < 0 || y1 > SCREEN_HEIGHT))
		return ;
	step_x = x0 < x1 ? 1 : -1;
	step_y = y0 < y1 ? 1 : -1;
	err = delta_x - delta_y;
	x = x0;
	y = y0;
	while (x != x1 || y != y1)
	{
		// printf("(%d, %d)\n", x, y);
		if ((x >= 0 && x <= SCREEN_WIDTH) && (y >= 0 && y <= SCREEN_HEIGHT))
			my_mlx_pixel_put(img, x, y, color);
		e2 = 2 * err;
		if (e2 > -delta_y)
		{
			err -= delta_y;
			x += step_x;
		}
		if (e2 < delta_x)
		{
			err += delta_x;
			y += step_y;
		}
	}
}

#define SPACE 4

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

	// draw_cross(&img);

	printf("window size: (%4d,%4d)\n", SCREEN_WIDTH, SCREEN_HEIGHT);
	int x_draw = 0;
	int y_draw = 0;
	int x_prev = 0;
	int y_prev = 0;
	int color = 0;

	
	//Draw horizontal lines
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->wide; j++)
		{
			// Calculate the offset from the center of the map to the center of the window
			x_prev = x_draw;
			y_prev = y_draw;

			// Calculate the coordinates to draw the point

			x_draw = window_center_x + (j - map_center_y) * SPACE;
			y_draw = window_center_y + (i - map_center_x) * SPACE;
			y_draw -= points[i][j].height;

			color = get_color(points[i][j].color);
			if (j != 0)
				bresenham_line(&img, x_prev, y_prev, x_draw, y_draw, color);
		}
	}

	// Draw vertical lines
	for (int j = 0; j < map->wide; j++)
	{
		for (int i = 0; i < map->height; i++)
		{
			// Calculate the offset from the center of the map to the center of the window
			x_prev = x_draw;
			y_prev = y_draw;
			// Calculate the coordinates to draw the point
			x_draw = window_center_x + (j - map_center_y) * SPACE;
			y_draw = window_center_y + (i - map_center_x) * SPACE;
			y_draw -= points[i][j].height;

			color = get_color(points[i][j].color);
			if (i != 0)
				bresenham_line(&img, x_prev, y_prev, x_draw, y_draw, color);
		}
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
