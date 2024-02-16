/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:19:58 by psegura-          #+#    #+#             */
/*   Updated: 2024/02/16 21:37:33 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

const int	a[][3] = {
	{2, 0, 1},
	{3, 0, 0},
	{5, 1, 1},
};

const int	b[][3] = {
	{1, 0, 1},
	{1, 2, 1},
	{1, 1, 0},
};


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

void draw_points(t_map *map, t_mlx *mlx) {
    t_data img;
    t_point **points = map->map;

    img.img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    // Calculate the center of the map
    int map_center_x = map->height / 2;
    int map_center_y = map->wide / 2;

    // Calculate the center of the window
    int window_center_x = SCREEN_WIDTH / 2;
    int window_center_y = SCREEN_HEIGHT / 2;

    draw_cross(&img);

    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->wide; j++) {
            // Calculate the offset from the center of the map to the center of the window
            int x_offset = (j - map_center_y) * 20;
            int y_offset = (i - map_center_x) * 20;

            // Calculate the coordinates to draw the point
            int x_draw = window_center_x + x_offset;
            int y_draw = window_center_y + y_offset;

            // Draw the point
            my_mlx_pixel_put(&img, x_draw, y_draw, get_color(points[i][j].color));
        }
    }

    mlx_put_image_to_window(mlx->mlx, mlx->win, img.img, 0, 0);
}


void	init_data(t_map *map, char *input_file)
{
	ft_memset(map, 0, sizeof(t_map));
	create_map_matrix(map, input_file);
	printf("map height: [%d] map wide: [%d] map pointer: [%p]\n", map->height, map->wide, map->map);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_mlx	mlx;

	if (argc != 2)
		exit(EXIT_FAILURE);
	
	init_data(&map, argv[1]);

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "FDF");

	draw_points(&map, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, ft_input, &mlx);
	mlx_hook(mlx.win, 17, 0, ft_input, &mlx);

	mlx_loop(mlx.mlx);
	
	exit_program(map.map);
	// system("leaks -q fdf");
	return (0);
}
