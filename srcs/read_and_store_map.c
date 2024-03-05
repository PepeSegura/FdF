/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_store_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:53:09 by psegura-          #+#    #+#             */
/*   Updated: 2024/03/05 18:50:33 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	wide_map(char **map)
{
	char	**aux;
	int		wide = 0;
	int		prev = 0;
	int		i = -1;

	while (map[++i])
	{
		prev = wide;
		aux = ft_split(map[i], ' ');
		if (!aux)
			return (0);
		wide = ft_len_matrix(aux);
		ft_free_matrix(aux);
		if (prev != wide && i != 0)
			ft_print_error("Not all the lines have the same number of points.");
	}
	return (wide);
}

int	get_color(char *color)
{
	if (color == NULL)
		return (0x00FFFFFF);
	return (ft_atol_16(color + 1));
}

t_point	store_point_info(int x, int y, char *str)
{
	t_point	point;
	char	*aux;

	point.x = x;
	point.y = y;
	point.height = ft_atoi(str);
	aux = ft_strchr(str, ',');
	point.color = get_color(aux);
	return (point);
}

t_point	**store_map_info(t_map *info, char **map, int i, int j)
{
	t_point	**map_info;
	int		len;
	int		wide;
	char	**line_points;

	len = ft_len_matrix(map);
	wide = wide_map(map);
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
	info->height = len;
	info->wide = wide;
	return (map_info);
}

t_point	**create_map_matrix(t_map *info, char *filename)
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
	final_map = store_map_info(info, map, 0, 0);
	close(fd);
	ft_free_matrix(map);
	info->map = final_map;
	return (final_map);
}
