/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:26:09 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/08 18:58:38 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <fcntl.h>
#include <unistd.h>

void	clean_free(char **split, char *line)
{
	free_split(split);
	free(line);
}
void	print_progress(int current, int total, int points)
{
	ft_printf("\r\033[34m📖 Lecture: \033[33m%d%%\033[34m | Points: \033[33m%d",
		(current * 100) / total, points);
}

// Verifier les dimensions de la map
void	check_file2(char *filename)
{
	int		fd;
	char	*line;
	char	**split;
	int		width;
	int		count;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	split = ft_split(line, ' ');
	width = -1;
	while (split[++width]);
	clean_free(split, line);
	line = get_next_line(fd);
	while (line)
	{
		count = -1;
		split = ft_split(line, ' ');
		while (split[++count]);
		if (count != width)
			error_close_window(4, filename);
		clean_free(split, line);
		line = get_next_line(fd);
	}
	close(fd);
}

// Verifier le fd du fichier
void	check_file(char *filename)
{
	int	fd;

	if (!filename || !filename[0])
		error_close_window(1, filename);
	fd = open(filename, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		error_close_window(2, filename);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_close_window(3, filename);
	close(fd);
	check_file2(filename);
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
