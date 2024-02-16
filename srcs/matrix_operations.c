/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:01:52 by psegura-          #+#    #+#             */
/*   Updated: 2024/02/16 22:48:15 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// const int	a[][3] = {
// 	{2, 0, 1},
// 	{3, 0, 0},
// 	{5, 1, 1},
// };

// const int	b[][3] = {
// 	{1, 0, 1},
// 	{1, 2, 1},
// 	{1, 1, 0},
// };

void	print_matrix(int size_x, int size_y, int **a)
{
	int	i;
	int	j;

	i = 0;
	while (i < size_x)
	{
		j = 0;
		while (j < size_y)
		{
			printf("[%d] ", a[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	**create_matrix(int size_x, int size_y)
{
	int	**new_matrix;
	int	i;

	i = 0;
	new_matrix = malloc(size_x * sizeof(int *));
	if (new_matrix == NULL)
		exit(EXIT_FAILURE);
	while (i < size_x)
	{
		new_matrix[i] = malloc(size_y * sizeof(int));
		if (new_matrix[i] == NULL)
			exit(EXIT_FAILURE);
		i++;
	}
	return (new_matrix);
}

int	**matrix_adition(int size_x, int size_y,
		const int a[size_x][size_y], const int b[size_x][size_y])
{
	int	**final;
	int	i;
	int	j;

	final = create_matrix(size_x, size_y);
	i = -1;
	while (++i < size_x)
	{
		j = -1;
		while (++j < size_y)
			final[i][j] = a[i][j] + b[i][j];
	}
	print_matrix(size_x, size_y, final);
	return (final);
}

int	**matrix_multiplication(int size_x, int size_y,
		const int a[size_x][size_y], const int b[size_x][size_y])
{
	int	**final;
	int	i;
	int	j;
	int	k;

	final = create_matrix(size_x, size_y);
	i = -1;
	while (++i < size_x)
	{
		j = -1;
		while (++j < size_y)
		{
			final[i][j] = 0;
			k = -1;
			while (++k < size_y)
				final[i][j] += a[i][k] * b[k][j];
		}
	}
	print_matrix(size_x, size_y, final);
	return (final);
}
