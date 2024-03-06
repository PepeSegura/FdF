/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:20:32 by psegura-          #+#    #+#             */
/*   Updated: 2024/03/06 17:05:10 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*__Header_files__*/
# include "libs.h"
# include "defines.h"

/*__Libft__*/
# include "../libft/inc/libft.h"

enum e_modes {
  ZOOM_IN,
  ZOOM_OUT,
  SCALE_IN,
  SCALE_OUT,
  MOVE_UP,
  MOVE_DOWN,
  MOVE_RIGHT,
  MOVE_LEFT,
};

typedef struct	s_data {
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

/*__Matrix_Operations__*/
void	print_matrix(int size_x, int size_y, int **a);
int		**create_matrix(int size_x, int size_y);
int		**matrix_adition(int size_x, int size_y,
			const int a[size_x][size_y], const int b[size_x][size_y]);
int		**matrix_multiplication(int size_x, int size_y,
			const int a[size_x][size_y], const int b[size_x][size_y]);

t_point	**create_map_matrix(t_map *info, char *filename);

void	ft_print_error(char *str);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	bresenham_line(t_fdf *fdf, t_point prev, t_point new);

#endif
