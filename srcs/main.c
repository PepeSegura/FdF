/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:38:11 by psegura-          #+#    #+#             */
/*   Updated: 2024/03/06 04:30:49 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_points(t_fdf *fdf, t_mlx *mlx);

void	modify_zoom(int *value, int flag)
{
	if (flag == ZOOM_IN || flag == SCALE_IN)
		(*value) = (*value) * 2;
	else if (flag == ZOOM_OUT || flag == SCALE_OUT)
		(*value) = (*value) / 2;
	if (*value == 0 && flag != SCALE_OUT)
		(*value) = 1;

}

void	translation(int *value, int flag)
{
	if (flag == MOVE_LEFT)
		(*value) = (*value - SCREEN_WIDTH / 10);
	if (flag == MOVE_RIGHT)
		(*value) = (*value + SCREEN_WIDTH / 10);
	if (flag == MOVE_UP)
		(*value) = (*value - SCREEN_HEIGHT / 10);
	if (flag == MOVE_DOWN)
		(*value) = (*value + SCREEN_HEIGHT / 10);
}

int	ft_exit(void)
{
	exit(EXIT_SUCCESS);
}
int	ft_input(int keycode, t_fdf *fdf)
{
	printf("key: [%d]\n", keycode);
	if (keycode == PLUS)
		modify_zoom(&fdf->zoom, ZOOM_IN);
	else if (keycode == MINUS)
		modify_zoom(&fdf->zoom, ZOOM_OUT);
	else if (keycode == W)
		modify_zoom(&fdf->scale, SCALE_IN);
	else if (keycode == S)
		modify_zoom(&fdf->scale, SCALE_OUT);
	else if (keycode == UP)
		translation(&fdf->translate_y, MOVE_UP);
	else if (keycode == DOWN)
		translation(&fdf->translate_y, MOVE_DOWN);
	else if (keycode == LEFT)
		translation(&fdf->translate_x, MOVE_LEFT);
	else if (keycode == RIGHT)
		translation(&fdf->translate_x, MOVE_RIGHT);
	else if (keycode == 114)
	{
		fdf->scale = 1;
		fdf->translate_x = 0;
		fdf->translate_y = 0;
		fdf->zoom = SCREEN_WIDTH / fdf->map.wide;
	}
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

// cos(θ)	-sin(θ)	0		X
// sin(θ)	 cos(θ)	0		Y
// 0			0	1		Z

void	rotate_point(int *x, int *y, int *z)
{
	double	theta;
	double	final_x;
	double	final_y;
	double	final_z;

	theta = M_PI / 4.0;
	final_x = (cos(theta) * (*x)) + (-sin(theta) * (*y)) + (0 * (*z));
	final_y = (sin(theta) * (*x)) + (cos(theta) * (*y)) + (0 * (*z));
	final_z = (0 * (*x)) + (0 * (*y)) + (1 * (*z));
	(*x) = final_x;
	(*y) = final_y;
	(*z) = final_z;
}

void draw_points(t_fdf *fdf, t_mlx *mlx)
{
	t_data img;
	t_point **points = fdf->map.map;
	t_map	map = fdf->map;
	t_point	prev;
	t_point	new;

	img.img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	// Calculate the center of the map
	int map_center_x = map.height / 2;
	int map_center_y = map.wide / 2;

	double window_center_x = (SCREEN_WIDTH / 2);
	double window_center_y = (SCREEN_HEIGHT / 2);

	printf("window size: (%4d,%4d)\n", SCREEN_WIDTH, SCREEN_HEIGHT);

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
				bresenham_line(&img, prev, new);
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
				bresenham_line(&img, prev, new);
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, 0, 0);
}

void	init_data(t_fdf *fdf, char *input_file)
{
	create_map_matrix(&fdf->map, input_file);
	if (fdf->map.wide == 0 || fdf->map.height == 0)
		ft_print_error("Empty map.");
	fdf->zoom = (SCREEN_WIDTH / fdf->map.wide) / 2;
	fdf->scale = 1;
	printf("map height: [%d] map wide: [%d]\n", fdf->map.height, fdf->map.wide);
	printf("scale: %d\n", fdf->zoom);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		ft_print_error("Not enought arguments.");
	ft_memset(&fdf, 0, sizeof(t_fdf));
	init_data(&fdf, argv[1]);
	fdf.mlx.mlx = mlx_init();
	fdf.mlx.win = mlx_new_window(fdf.mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "FDF");
	draw_points(&fdf, &fdf.mlx);
	mlx_hook(fdf.mlx.win, 2, 1L << 0, ft_input, &fdf);
	mlx_hook(fdf.mlx.win, 17, 0, ft_exit, &fdf);
	mlx_loop(fdf.mlx.mlx);
	return (0);
}
