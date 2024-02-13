/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_row_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:49:01 by psegura-          #+#    #+#             */
/*   Updated: 2024/02/13 14:45:32 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_add_row_matrix(char **matrix, char *new_row)
{
	int		i;
	char	**new_matrix;
	int		len_matrix;

	if (!matrix)
		return (NULL);
	len_matrix = ft_len_matrix(matrix);
	new_matrix = ft_calloc(sizeof(char *), (len_matrix + 2));
	if (!new_matrix)
		return (NULL);
	if (!new_row)
		return (matrix);
	i = 0;
	while (i < len_matrix)
	{
		new_matrix[i] = matrix[i];
		i++;
	}
	new_matrix[i] = new_row;
	free(matrix);
	return (new_matrix);
}
