/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:38:07 by psegura-          #+#    #+#             */
/*   Updated: 2024/03/08 20:09:08 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	modify_translation(int *value, int flag, t_fdf *fdf)
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

void	zoom(int key, t_fdf *fdf)
{
	if (key == PLUS)
	{
		modify_zoom(&fdf->zoom, ZOOM_IN, fdf);
		modify_zoom(&fdf->scale, SCALE_IN, fdf);
	}
	else if (key == MINUS)
	{
		modify_zoom(&fdf->zoom, ZOOM_OUT, fdf);
		modify_zoom(&fdf->scale, SCALE_OUT, fdf);
	}
	else if (key == W)
		modify_zoom(&fdf->scale, SCALE_IN, fdf);
	else if (key == S)
		modify_zoom(&fdf->scale, SCALE_OUT, fdf);
}

void	translation(int key, t_fdf *fdf)
{
	if (key == UP)
		modify_translation(&fdf->translate_y, MOVE_UP, fdf);
	else if (key == DOWN)
		modify_translation(&fdf->translate_y, MOVE_DOWN, fdf);
	else if (key == LEFT)
		modify_translation(&fdf->translate_x, MOVE_LEFT, fdf);
	else if (key == RIGHT)
		modify_translation(&fdf->translate_x, MOVE_RIGHT, fdf);
}

int	ft_input(int key, t_fdf *fdf)
{
	printf("key: [%d]\n", key);
	if (key == PLUS || key == MINUS || key == W || key == S)
		zoom(key, fdf);
	else if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
		translation(key, fdf);
	else if (key == R)
	{
		fdf->scale = 1;
		fdf->translate_x = 0;
		fdf->translate_y = 0;
		fdf->zoom = (fdf->screen_width / fdf->map.wide) / 2;
	}
	else if (key == ESC)
		exit(EXIT_SUCCESS);
	draw_points(fdf, &fdf->mlx);
	return (0);
}
