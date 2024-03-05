/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:38:11 by psegura-          #+#    #+#             */
/*   Updated: 2024/03/05 21:44:41 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_points(t_fdf *fdf, t_mlx *mlx);

void	modify_zoom(int *zoom, int flag)
{
	if (*zoom == 0 && flag != MOVE_LEFT)
		(*zoom) = 1;
	if (flag == ZOOM_IN || flag == SCALE_IN)
		(*zoom) = (*zoom) * 2;
	else if (flag == ZOOM_OUT || flag == SCALE_OUT)
		(*zoom) = (*zoom) / 2;
	if (flag == MOVE_LEFT)
		(*zoom) = (*zoom - SCREEN_WIDTH / 10);
	if (flag == MOVE_RIGHT)
		(*zoom) = (*zoom + SCREEN_WIDTH / 10);
}

int	ft_exit(void)
{
	exit(EXIT_SUCCESS);
}
int	ft_input(int keycode, t_fdf *fdf)
{
	printf("key: [%d]\n", keycode);
	if (keycode == UP)
		modify_zoom(&fdf->zoom, ZOOM_IN);
	else if (keycode == DOWN)
		modify_zoom(&fdf->zoom, ZOOM_OUT);
	else if (keycode == W)
		modify_zoom(&fdf->scale, SCALE_IN);
	else if (keycode == S)
		modify_zoom(&fdf->scale, SCALE_OUT);
	else if (keycode == LEFT)
		modify_zoom(&fdf->translate, MOVE_LEFT);
	else if (keycode == RIGHT)
		modify_zoom(&fdf->translate, MOVE_RIGHT);
	else if (keycode == ESC)
		exit(EXIT_SUCCESS);
	draw_points(fdf, &fdf->mlx);
	return (0);
}

void	exit_program(t_point **map)
{
	ft_free_matrix((char **)map);
	exit(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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
		if ((x >= 0 && x < SCREEN_WIDTH) && (y >= 0 && y < SCREEN_HEIGHT))
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

void draw_points(t_fdf *fdf, t_mlx *mlx)
{
	t_data img;
	t_point **points = fdf->map.map;
	t_map	map = fdf->map;

	img.img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	// Calculate the center of the map
	int map_center_x = map.height / 2;
	int map_center_y = map.wide / 2;

	double window_center_x = (SCREEN_WIDTH / 2);
	double window_center_y = (SCREEN_HEIGHT / 2);

	printf("window size: (%4d,%4d)\n", SCREEN_WIDTH, SCREEN_HEIGHT);
	int x_draw = 0;
	int y_draw = 0;
	int x_prev = 0;
	int y_prev = 0;
	
	//Draw horizontal lines
	for (int i = 0; i < map.height; i++)
	{
		for (int j = 0; j < map.wide; j++)
		{
			// Calculate the offset from the center of the map to the center of the window
			x_prev = x_draw;
			y_prev = y_draw;

			// Calculate the coordinates to draw the point

			x_draw = (window_center_x + (j - map_center_y) * fdf->zoom) + fdf->translate;
			y_draw = (window_center_y + (i - map_center_x) * fdf->zoom);
			y_draw -= points[i][j].height * fdf->scale;

			if (j != 0)
				bresenham_line(&img, x_prev, y_prev, x_draw, y_draw, points[i][j].color);
		}
	}

	// Draw vertical lines
	for (int j = 0; j < map.wide; j++)
	{
		for (int i = 0; i < map.height; i++)
		{
			// Calculate the offset from the center of the map to the center of the window
			x_prev = x_draw;
			y_prev = y_draw;
			// Calculate the coordinates to draw the point
			x_draw = (window_center_x + (j - map_center_y) * fdf->zoom) + fdf->translate;
			y_draw = (window_center_y + (i - map_center_x) * fdf->zoom);
			y_draw -= points[i][j].height * fdf->scale;

			if (i != 0)
				bresenham_line(&img, x_prev, y_prev, x_draw, y_draw, points[i][j].color);
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, 0, 0);
}

void	init_data(t_fdf *fdf, char *input_file)
{
	create_map_matrix(&fdf->map, input_file);
	if (fdf->map.wide == 0 || fdf->map.height == 0)
		ft_print_error("Empty map.");
	fdf->zoom = SCREEN_WIDTH / fdf->map.wide;
	printf("map height: [%d] map wide: [%d]\n", fdf->map.height, fdf->map.wide);
	printf("scale: %d\n", fdf->zoom);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		ft_print_error("Not enought arguments.");
	ft_memset(&fdf, 0, sizeof(t_fdf));
	fdf.zoom = 2;
	fdf.scale = 1;
	init_data(&fdf, argv[1]);
	fdf.mlx.mlx = mlx_init();
	fdf.mlx.win = mlx_new_window(fdf.mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "FDF");
	draw_points(&fdf, &fdf.mlx);
	mlx_hook(fdf.mlx.win, 2, 1L << 0, ft_input, &fdf);
	mlx_hook(fdf.mlx.win, 17, 0, ft_exit, &fdf);
	mlx_loop(fdf.mlx.mlx);
	return (0);
}
