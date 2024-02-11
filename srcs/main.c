/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:19:58 by psegura-          #+#    #+#             */
/*   Updated: 2024/02/11 19:44:37 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_line_size(t_list **map, char *line, int y)
{
	char	**points;
	t_point	*point;
	int		points_nbr;
	int		x;

	if (!line)
		return ;
	points = ft_split(line, ' ');
	points_nbr = ft_len_matrix(points);

	// printf("Line: [%d] Points: [%d]\n", ft_strlen(line), points_nbr);
	// for (int x = 0; x < points_nbr; x++)
	x = 0;
	while (x < points_nbr)
	{
		point = ft_calloc(1, sizeof(t_point));
		point->x = x;
		point->y = y;
		point->height = ft_atoi(points[x]);
		point->color = ft_strchr(points[x], ',');
		if (point->color)
			point->color = ft_strdup(point->color + 1);
		// printf("\tX: [%d] Y:[%d] Height: [%d] Color: [%s]\n", x, y, point->height, point->color);
		ft_lstadd_front(map, ft_lstnew(point));
		// free(point);
		x++;
	}
	// printf("\n\n");
	ft_free_matrix(points);
}

// void	open_map(const char *filename)
// {
// 	int		fd;
// 	char	*line;
// 	char	*aux;
// 	int		y;

// 	fd = open(filename, O_RDONLY);
// 	y = 0;
// 	while (1)
// 	{
// 		aux = get_next_line(fd);
// 		if (!aux)
// 			break ;
// 		line = ft_strtrim(aux, "\n");
// 		free(aux);
// 		if (!line)
// 			break ;
// 		y++;
// 		print_line_size(line, y);
// 		free(line);
// 	}
// }

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

void	create_stack(t_list **map, char *filename)
{
	(void)map;
	int		fd;
	char	*line;
	char	*aux;
	int		y;

	fd = open(filename, O_RDONLY);
	y = 0;
	while (1)
	{
		aux = get_next_line(fd);
		if (!aux)
			break ;
		line = ft_strtrim(aux, "\n");
		free(aux);
		if (!line)
			break ;
		y++;
		print_line_size(map, line, y);
		free(line);
	}
}

void	print_lst_map(t_list *map)
{
	t_point	*content;
	int	y = 0;

	while (map)
	{
		content = map->content;
		if (content->y != y || y == 0)
		{
			printf("\nLine [%d]\n", y);
			y = content->y;
		}
		printf("\tX: [%d] Y: [%d] H: [%d] Color: [%s]\n", content->x, content->y, content->height, content->color);
		map = map->next;
	}
}

int	main(int argc, char **argv)
{
	t_list	*map;

	(void)argc, (void)argv;
	if (argc != 2)
		exit(EXIT_FAILURE);
	map = NULL;
	create_stack(&map, argv[1]);
	print_lst_map(map);
	// open_map(argv[1]);
	printf("\n");
	// system("leaks -q fdf");
	return (0);
}

