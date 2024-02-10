/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:19:58 by psegura-          #+#    #+#             */
/*   Updated: 2024/02/10 21:16:27 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_line_size(char *line)
{
	if (!line)
		return ;
	char **points = ft_split(line, ' ');
	printf("Line: [%d] Points: [%d]\n", ft_strlen(line), ft_len_matrix(points));
	ft_free_matrix(points);
}

void	open_map(const char *filename)
{
	int fd = open(filename, O_RDONLY);
	char *line;
	while (1)
	{
		line = get_next_line(fd);
		print_line_size(line);
		// printf("%s", line);
		if (!line)
			break ;
		free(line);
	}
}

const int a[][3] = {
	{2, 0, 1},
	{3, 0, 0},
	{5, 1, 1},
};

const int b[][3] = {
	{1, 0, 1},
	{1, 2, 1},
	{1, 1, 0},
};

int **matrix_adition(int size_x, int size_y, const int a[size_x][size_y], const int b[size_x][size_y])
{
	int	**addedd = malloc(size_x * sizeof(int *));
	for (int i = 0; i < size_x; i++)
	{
		addedd[i] = malloc(size_y * sizeof(int));
	}
	
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			addedd[i][j] = a[i][j] + b[i][j];
		}
	}

	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			printf("[%d] ", addedd[i][j]);
		}
		printf("\n");
	}
	return (addedd);
}

int	main(int argc, char **argv)
{
	(void)argc, (void)argv;
	if (argc != 2)
		exit(EXIT_FAILURE);
	// matrix_adition(3, 3, a, b);
	open_map(argv[1]);
	return (0);
}
