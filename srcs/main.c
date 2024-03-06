/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:38:11 by psegura-          #+#    #+#             */
/*   Updated: 2024/03/06 20:49:10 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_points(t_fdf *fdf, t_mlx *mlx);

void	modify_zoom(int *value, int flag, t_fdf *fdf)
{
	if (flag == ZOOM_IN || flag == SCALE_IN)
		(*value) = (*value) * 2;
	else if (flag == ZOOM_OUT || flag == SCALE_OUT)
		(*value) = (*value) / 2;
	if (*value == 0 && flag != SCALE_OUT)
		(*value) = 1;
	if (*value > fdf->screen_width / 2)
		(*value) = fdf->screen_width / 2;

}

void	translation(int *value, int flag, t_fdf *fdf)
{
	if (flag == MOVE_LEFT)
		(*value) = (*value - fdf->screen_width / 10);
	if (flag == MOVE_RIGHT)
		(*value) = (*value + fdf->screen_width / 10);
	if (flag == MOVE_UP)
		(*value) = (*value - fdf->screen_height / 10);
	if (flag == MOVE_DOWN)
		(*value) = (*value + fdf->screen_height / 10);
}

int	ft_exit(void)
{
	exit(EXIT_SUCCESS);
}
int	ft_input(int keycode, t_fdf *fdf)
{
	printf("key: [%d]\n", keycode);
	if (keycode == PLUS)
		modify_zoom(&fdf->zoom, ZOOM_IN, fdf);
	else if (keycode == MINUS)
		modify_zoom(&fdf->zoom, ZOOM_OUT, fdf);
	else if (keycode == W)
		modify_zoom(&fdf->scale, SCALE_IN, fdf);
	else if (keycode == S)
		modify_zoom(&fdf->scale, SCALE_OUT, fdf);
	else if (keycode == UP)
		translation(&fdf->translate_y, MOVE_UP, fdf);
	else if (keycode == DOWN)
		translation(&fdf->translate_y, MOVE_DOWN, fdf);
	else if (keycode == LEFT)
		translation(&fdf->translate_x, MOVE_LEFT, fdf);
	else if (keycode == RIGHT)
		translation(&fdf->translate_x, MOVE_RIGHT, fdf);
	else if (keycode == R)
	{
		fdf->scale = 1;
		fdf->translate_x = 0;
		fdf->translate_y = 0;
		fdf->zoom = (fdf->screen_width / fdf->map.wide) / 2;
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

#ifdef OSX
void	set_screen_data(int *screen_width, int *screen_height)
{
	CGDirectDisplayID	display_id;
	CGRect				screen_bounds;
	int	width;
	int	height;

	display_id = kCGDirectMainDisplay;
	screen_bounds = CGDisplayBounds(display_id);
	width = CGRectGetWidth(screen_bounds);
	height = CGRectGetHeight(screen_bounds);
	(*screen_width) =  SCREEN_WIDTH;
	(*screen_height) = SCREEN_HEIGHT;
	if (SCREEN_WIDTH > width)
		(*screen_width) = width;
	if (SCREEN_HEIGHT > height)
		(*screen_height) = height;
	
}
#else
void	set_screen_data(int *screen_width, int *screen_height)
{
	(*screen_width) = SCREEN_WIDTH;
	(*screen_height) = SCREEN_HEIGHT;
}
#endif

void	init_data(t_fdf *fdf, char *input_file)
{
	create_map_matrix(&fdf->map, input_file);
	if (fdf->map.wide == 0 || fdf->map.height == 0)
		ft_print_error("Empty map.");
	set_screen_data(&fdf->screen_width, &fdf->screen_height);
	fdf->zoom = (fdf->screen_width / fdf->map.wide) / 2;
	fdf->scale = 1;
	printf("map height: [%d] map wide: [%d]\n", fdf->map.height, fdf->map.wide);
	printf("scale: %d\n", fdf->zoom);
	fdf->mlx.mlx = mlx_init();
	fdf->mlx.win = mlx_new_window(fdf->mlx.mlx, fdf->screen_width, fdf->screen_height, "FDF");
	fdf->img.img = mlx_new_image(fdf->mlx.mlx, fdf->screen_width, fdf->screen_height);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel, &fdf->img.line_length, &fdf->img.endian);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		ft_print_error("Not enought arguments.");
	ft_memset(&fdf, 0, sizeof(t_fdf));
	init_data(&fdf, argv[1]);

	draw_points(&fdf, &fdf.mlx);
	mlx_hook(fdf.mlx.win, 2, 1L << 0, ft_input, &fdf);
	mlx_hook(fdf.mlx.win, 17, 0, ft_exit, &fdf);
	mlx_loop(fdf.mlx.mlx);
	return (0);
}
