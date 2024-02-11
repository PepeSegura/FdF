/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:20:32 by psegura-          #+#    #+#             */
/*   Updated: 2024/02/11 15:10:09 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*__Header_files__*/
# include "libs.h"
# include "defines.h"

/*__Libft__*/
# include "../libft/inc/libft.h"

typedef struct s_point
{
	int		x;
	int		y;
	int		height;
	char	*color;
}	t_point;

/*__Matrix_Operations__*/
void	print_matrix(int size_x, int size_y, int **a);
int		**create_matrix(int size_x, int size_y);
int		**matrix_adition(int size_x, int size_y,
		const int a[size_x][size_y], const int b[size_x][size_y]);
int		**matrix_multiplication(int size_x, int size_y,
		const int a[size_x][size_y], const int b[size_x][size_y]);

#endif
