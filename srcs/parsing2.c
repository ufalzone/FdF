/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:26:09 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/07 17:40:10 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	print_progress(int current, int total, int points)
{
	ft_printf("\r\033[34m📖 Lecture: \033[33m%d%%\033[34m | Points: \033[33m%d",
		(current * 100) / total, points);
}

void	check_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("\033[31m❌ Erreur: Impossible d'ouvrir '%s'\033[0m\n",
			filename);
		exit(1);
	}
	close(fd);
}

// Obtenir Z min et max pour color
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
	line = get_next_line(fd);
	while (line)
	{
		split = ft_split(line, ' ');
		i = -1;
		while (split[++i])
		{
			z = ft_atoi(split[i]);
			map->z_min = fmin(map->z_min, z);
			map->z_max = fmax(map->z_max, z);
		}
		free(line);
		free_split(split);
		line = get_next_line(fd);
	}
	close(fd);
}
