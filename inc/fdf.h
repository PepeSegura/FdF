/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:20:32 by psegura-          #+#    #+#             */
/*   Updated: 2024/02/25 16:11:41 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*__Header_files__*/
# include "libs.h"
# include "defines.h"

/*__Libft__*/
# include "../libft/inc/libft.h"

# define X 0
# define Y 1
# define H 2

typedef struct s_point
{
	int		x;
	int		y;
	int		height;
	int		cords[3];
	int		relative[3];
	char	*color;
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

/*__Matrix_Operations__*/
void	print_matrix(int size_x, int size_y, int **a);
int		**create_matrix(int size_x, int size_y);
int		**matrix_adition(int size_x, int size_y,
			const int a[size_x][size_y], const int b[size_x][size_y]);
int		**matrix_multiplication(int size_x, int size_y,
			const int a[size_x][size_y], const int b[size_x][size_y]);

t_point	**create_map_matrix(t_map *info, char *filename);

void	ft_print_error(char *str);

#endif
