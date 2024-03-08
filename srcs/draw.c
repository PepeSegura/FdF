/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:41:36 by psegura-          #+#    #+#             */
/*   Updated: 2024/03/08 22:07:18 by psegura-         ###   ########.fr       */
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
	int	j;

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

#define HORIZONTAL	1
#define VERTICAL	0

#define I 0
#define J 1

void	get_new_point_data(t_draw *d, t_point **points, t_fdf *fdf, int flag)
{
	if (flag == HORIZONTAL)
	{
		d->new.x = (d->win_mid_x + (d->id[J] - d->map_mid_y) * fdf->zoom);
		d->new.y = (d->win_mid_y + (d->id[I] - d->map_mid_x) * fdf->zoom);
		d->new.y -= points[d->id[I]][d->id[J]].height * fdf->scale;
		rotate_point(&d->new.x, &d->new.y, &points[d->id[I]][d->id[J]].height);
		d->new.color = points[d->id[I]][d->id[J]].color;
	}
	else if (flag == VERTICAL)
	{
		d->new.x = (d->win_mid_x + (d->id[I] - d->map_mid_y) * fdf->zoom);
		d->new.y = (d->win_mid_y + (d->id[J] - d->map_mid_x) * fdf->zoom);
		d->new.y -= points[d->id[J]][d->id[I]].height * fdf->scale;
		rotate_point(&d->new.x, &d->new.y, &points[d->id[J]][d->id[I]].height);
		d->new.color = points[d->id[J]][d->id[I]].color;
	}
	d->new.x += fdf->translate_x;
	d->new.y += fdf->translate_y;
}

void	draw_loop(t_draw *d, t_fdf *fdf, t_flag *f, int flag)
{
	const t_map	map = fdf->map;

	d->id[I] = 0;
	while (d->id[I] < f->rows)
	{
		d->id[J] = 0;
		while (d->id[J] < f->columns)
		{
			d->prev.x = d->new.x;
			d->prev.y = d->new.y;
			get_new_point_data(d, map.map, fdf, flag);
			if (d->id[J] != 0)
				bresenham_line(fdf, d->prev, d->new);
			d->id[J]++;
		}
		d->id[I]++;
	}
}

void	draw_points(t_fdf *fdf, t_mlx *mlx)
{
	const t_map	map = fdf->map;
	t_draw		d;
	t_flag		flag;

	ft_memset(&d, 0, sizeof(t_draw));
	ft_memset(&flag, 0, sizeof(t_flag));
	clear_img(fdf);
	d.map_mid_x = map.height / 2;
	d.map_mid_y = map.wide / 2;
	d.win_mid_x = (fdf->screen_width / 2);
	d.win_mid_y = (fdf->screen_height / 2);
	flag.rows = map.height;
	flag.columns = map.wide;
	printf("window size: (%4d,%4d)\n", fdf->screen_width, fdf->screen_height);
	draw_loop(&d, fdf, &flag, HORIZONTAL);
	flag.rows = map.wide;
	flag.columns = map.height;
	draw_loop(&d, fdf, &flag, VERTICAL);
	mlx_put_image_to_window(mlx->mlx, mlx->win, fdf->img.img, 0, 0);
}
