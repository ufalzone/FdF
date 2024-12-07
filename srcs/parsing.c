/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:28:58 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/07 17:46:17 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <fcntl.h>

// Obtenir les dimensions de la map
static t_map	get_dimensions(char *filename)
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
	free_split(split);
	close(fd);
	return (map);
}

// Allocation de la map
static t_map	allocate_map(t_map map)
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

// Fonction auxiliaire pour traiter une ligne
static void	process_line(t_map *map, char **split, int j, int *total_points)
{
	int	i;

	i = 0;
	while (split[i])
	{
		map->grid[j][i].x = i;
		map->grid[j][i].y = j;
		map->grid[j][i].z = ft_atoi(split[i]);
		map->grid[j][i].color = get_color(map, map->grid[j][i].z);
		i++;
		(*total_points)++;
	}
}

// Remplir la map
static t_map	fill_map(t_map map, char *filename)
{
	int		fd;
	char	*line;
	char	**split;
	int		j;
	int		total_points;

	fd = open(filename, O_RDONLY);
	j = 0;
	total_points = 0;
	ft_printf("\n\033[34m📍 Début de la lecture...\033[0m\n\n");
	line = get_next_line(fd);
	while (line)
	{
		split = ft_split(line, ' ');
		process_line(&map, split, j, &total_points);
		print_progress(j + 1, map.height, total_points);
		free(line);
		free_split(split);
		j++;
		line = get_next_line(fd);
	}
	ft_printf("\n\033[34m✨ Lu: \033[33m%d\033[34m pts\033[0m\n", total_points);
	return (close(fd), map);
}

// Fonction principale de parsing
t_map	parse_map(char *filename)
{
	t_map	map;

	check_file(filename);
	map = get_dimensions(filename);
	if (map.width == 0 || map.height == 0)
	{
		ft_printf("\033[31m❌ Erreur: Fichier vide ou invalide\033[0m\n");
		exit(1);
	}
	get_z_min_max(&map, filename);
	map = allocate_map(map);
	if (!map.grid)
	{
		ft_printf("\033[31m❌ Erreur: Allocation mémoire échouée\033[0m\n");
		exit(1);
	}
	map = fill_map(map, filename);
	return (map);
}
