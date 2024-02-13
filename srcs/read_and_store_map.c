/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_store_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:53:09 by psegura-          #+#    #+#             */
/*   Updated: 2024/02/13 18:53:27 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	wide_map(char *line)
{
	char	**aux;
	int		wide;

	aux = ft_split(line, ' ');
	if (!aux)
		return (0);
	wide = ft_len_matrix(aux);
	ft_free_matrix(aux);
	return (wide);
}

t_point	store_point_info(int x, int y, char *str)
{
	t_point	point;
	char	*aux;

	point.x = x;
	point.y = y;
	point.height = ft_atoi(str);
	aux = ft_strchr(str, ',');
	point.color = NULL;
	if (aux)
		point.color = (aux + 1);
	return (point);
}
// point.color = ft_strdup(aux + 1);
// printf("x: [%d] y: [%d] h: [%d] c: [%s]\n", point.x, point.y, point.height, point.color);

t_point	**store_map_info(char **map, int i, int j)
{
	t_point	**map_info;
	int		len;
	int		wide;
	char	**line_points;

	len = ft_len_matrix(map);
	wide = wide_map(map[0]);
	map_info = (t_point **)ft_calloc((len + 1), sizeof(t_point *));
	while (map[i] != NULL)
	{
		line_points = ft_split(map[i], ' ');
		map_info[i] = (t_point *)ft_calloc((wide + 1), sizeof(t_point));
		j = -1;
		while (++j < wide)
			map_info[i][j] = store_point_info(i, j, line_points[j]);
		ft_free_matrix(line_points);
		i++;
	}
	return (map_info);
}

t_point	**create_map_matrix(char *filename)
{
	t_point	**final_map;
	char	**map;
	char	*line;
	char	*aux;
	int		fd;

	fd = open(filename, O_RDONLY);
	map = ft_calloc(1, sizeof(char *));
	while (1)
	{
		aux = get_next_line(fd);
		if (!aux)
			break ;
		line = ft_strtrim(aux, "\n");
		free(aux);
		if (!line)
			break ;
		map = ft_add_row_matrix(map, line);
	}
	final_map = store_map_info(map, 0, 0);
	close(fd);
	ft_free_matrix(map);
	return (final_map);
}
