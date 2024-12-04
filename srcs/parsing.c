/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:28:58 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/03 22:59:28 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_color(int value)
{
	if (value == 0)
		return (0xFFDAB9);  // Orange pêche
	else if (value <= 1)
		return (0xFFB6C1);  // Rose clair
	else if (value <= 2)
		return (0xFFA07A);  // Orange saumon clair
	else if (value <= 3)
		return (0xFF8C69);  // Orange saumon
	else if (value <= 4)
		return (0xFF69B4);  // Rose vif
	else if (value <= 5)
		return (0xFF1493);  // Rose profond
	else if (value <= 6)
		return (0xDA70D6);  // Orchidée moyen
	else if (value <= 7)
		return (0xBA55D3);  // Orchidée
	else if (value <= 8)
		return (0x9370DB);  // Violet moyen
	else if (value <= 9)
		return (0x8A2BE2);  // Bleu violet
	else
		return (0x800080);  // Violet
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
			map.grid[j][i].color = get_color(map.grid[j][i].z);
			i++;
		}
		free(line);
		// free_split(split);
		j++;
	}
	return (close(fd), map);
}

t_map	parse_map(char *filename)
{
	t_map	map;

	map = get_dimensions(filename);
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