/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:28:58 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/05 18:08:32 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
int	get_color(t_map *map, int value)
{
	float	normalized_value;

	if (map->z_max == map->z_min)
		normalized_value = 0;
	else
		normalized_value = (float)(value - map->z_min) / (map->z_max - map->z_min);
	printf("%f", normalized_value);
	if (normalized_value == 0)
		return (0xFFDAB9); // Orange pêche
	else if (normalized_value <= 0.1)
		return (0xFFB6C1); // Rose clair
	else if (normalized_value <= 0.2)
		return (0xFFA07A); // Orange saumon clair
	else if (normalized_value <= 0.3)
		return (0xFF8C69); // Orange saumon
	else if (normalized_value <= 0.4)
		return (0xFF69B4); // Rose vif
	else if (normalized_value <= 0.5)
		return (0xFF1493); // Rose profond
	else if (normalized_value <= 0.6)
		return (0xDA70D6); // Orchidée moyen
	else if (normalized_value <= 0.7)
		return (0xBA55D3); // Orchidée
	else if (normalized_value <= 0.8)
		return (0x9370DB); // Violet moyen
	else if (normalized_value <= 0.9)
		return (0x8A2BE2); // Bleu violet
	else
		return (0x800080); // Violet
}

t_map	get_dimensions(char *filename)
{
	t_map	map;
	int		fd;
	char	*line;
	char	**split;

	fd = open(filename, O_RDONLY);
	map.height = 0;
	line = get_next_line(fd);
	split = ft_split(line, ' ');
	map.width = 0;
	while (split[map.width])
		map.width++;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		map.height++;
	}
	// free_split(split);
	close(fd);
	return (map);
}

t_map	allocate_map(t_map map)
{
	int	i;

	map.grid = (t_point **)malloc(sizeof(t_point *) * map.height);
	if (!map.grid)
		return (map);
	i = 0;
	while (i < map.height)
	{
		map.grid[i] = (t_point *)malloc(sizeof(t_point) * map.width);
		if (!map.grid[i])
			return (map);
		i++;
	}
	return (map);
}

t_map	fill_map(t_map map, char *filename)
{
	int		fd;
	char	*line;
	char	**split;
	int		i;
	int		j;

	fd = open(filename, O_RDONLY);
	j = 0;
	while ((line = get_next_line(fd)))
	{
		split = ft_split(line, ' ');
		i = 0;
		while (split[i])
		{
			map.grid[j][i].x = i;
			map.grid[j][i].y = j;
			map.grid[j][i].z = ft_atoi(split[i]);
			map.grid[j][i].color = get_color(&map, map.grid[j][i].z);
			i++;
		}
		free(line);
		j++;
	}
	return (close(fd), map);
}
#include <stdio.h>

void	get_z_min_max(t_map *map, char *filename)
{
	int		fd;
	char	*line;
	char	**split;
	int		i;
	int		z;

	fd = open(filename, O_RDONLY);
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	while ((line = get_next_line(fd)))
	{
		split = ft_split(line, ' ');
		i = 0;
		while (split[i])
		{
			z = ft_atoi(split[i]);
			map->z_min = fmin(map->z_min, z);
			map->z_max = fmax(map->z_max, z);
			printf("%d, %d\n", map->z_max, map->z_min);
			i++;
		}
		free(line);
	}
	close(fd);
}

t_map	parse_map(char *filename)
{
	t_map	map;

	map = get_dimensions(filename);
	get_z_min_max(&map, filename);
	map = allocate_map(map);
	map = fill_map(map, filename);
	return (map);
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_map map;

// 	map = parse_map("test.fdf");
// 	ft_printf("width: %d\n", map.width);
// 	ft_printf("height: %d\n", map.height);
// 	int i;
// 	int j;
// 	i = 0;
// 	while (i < map.height)
// 	{
// 		j = 0;
// 		while (j < map.width)
// 		{
// 			printf("%3d ", map.grid[i][j].z);
// 			j++;
// 		}
// 		ft_printf("\n");
// 		i++;
// 	}
// 	return (0);
// }