/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:19:58 by psegura-          #+#    #+#             */
/*   Updated: 2024/02/13 19:04:26 by psegura-         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_point	**map;
	t_mlx	mlx;

	if (argc != 2)
		exit(EXIT_FAILURE);
	map = create_map_matrix(argv[1]);

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1920, 1080, "FDF");

	mlx_hook(mlx.win, 2, 1L << 0, ft_input, &mlx);
	mlx_hook(mlx.win, 17, 0, ft_input, &mlx);

	mlx_loop(mlx.mlx);
	
	exit_program(map);
	system("leaks -q fdf");
	return (0);
}
