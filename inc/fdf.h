/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:20:32 by psegura-          #+#    #+#             */
/*   Updated: 2024/03/08 22:07:15 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*__Header_files__*/
# include "libs.h"
# include "defines.h"

/*__Libft__*/
# include "../libft/inc/libft.h"

enum e_modes
{
	ZOOM_IN,
	ZOOM_OUT,
	SCALE_IN,
	SCALE_OUT,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_RIGHT,
	MOVE_LEFT,
};

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_point
{
	int		x;
	int		y;
	int		height;
	int		color;
}	t_point;

typedef struct s_flag
{
	int	rows;
	int	columns;
}	t_flag;

typedef struct s_draw
{
	int		id[2];
	double	win_mid_x;
	double	win_mid_y;
	int		map_mid_x;
	int		map_mid_y;
	t_point	prev;
	t_point	new;
}	t_draw;

typedef struct s_bresenham
{
	t_point	prev;
	t_point	new;
	int		delta_x;
	int		delta_y;
	int		step_x;
	int		step_y;
	int		err;
	int		x;
	int		y;
}	t_bresenham;

typedef struct s_map
{
	t_point	**map;
	int		height;
	int		wide;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_fdf
{
	t_mlx	mlx;
	t_map	map;
	t_data	img;
	int		zoom;
	int		scale;
	int		translate_x;
	int		translate_y;
	int		screen_width;
	int		screen_height;
}	t_fdf;

t_point	**create_map_matrix(t_map *info, char *filename);

void	set_screen_data(int *screen_width, int *screen_height);

void	draw_points(t_fdf *fdf, t_mlx *mlx);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	bresenham_line(t_fdf *fdf, t_point prev, t_point new);

float	fast_sqrt(float x);
void	rotate_point(int *x, int *y, int *z);

void	create_hooks(t_fdf *fdf);

int		ft_exit(void);
int		ft_input(int key, t_fdf *fdf);

void	ft_print_error(char *str);

#endif
