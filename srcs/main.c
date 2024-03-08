/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:38:11 by psegura-          #+#    #+#             */
/*   Updated: 2024/03/08 20:15:18 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_exit(void)
{
	exit(EXIT_SUCCESS);
}

void	init_data(t_fdf *fdf, char *input_file)
{
	ft_memset(fdf, 0, sizeof(t_fdf));
	create_map_matrix(&fdf->map, input_file);
	if (fdf->map.wide == 0 || fdf->map.height == 0)
		ft_print_error("Empty map.");
	set_screen_data(&fdf->screen_width, &fdf->screen_height);
	fdf->zoom = (fdf->screen_width / fdf->map.wide) / 2;
	fdf->scale = 1;
	fdf->mlx.mlx = mlx_init();
	fdf->mlx.win = mlx_new_window(fdf->mlx.mlx,
			fdf->screen_width, fdf->screen_height, "FDF");
	fdf->img.img = mlx_new_image(fdf->mlx.mlx,
			fdf->screen_width, fdf->screen_height);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img,
			&fdf->img.bits_per_pixel, &fdf->img.line_length, &fdf->img.endian);
}

void	create_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->mlx.win, 2, 1L << 0, ft_input, fdf);
	mlx_hook(fdf->mlx.win, 17, 0, ft_exit, fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		ft_print_error("Not enought arguments.");
	init_data(&fdf, argv[1]);
	draw_points(&fdf, &fdf.mlx);
	create_hooks(&fdf);
	mlx_loop(fdf.mlx.mlx);
	return (0);
}
