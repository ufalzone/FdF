/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:40:49 by ufalzone          #+#    #+#             */
/*   Updated: 2024/11/29 23:29:46 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"
#include "includes/mlx.h"

int	main(void)
{
	void *mlx;
	void *win;
	t_map map;
	int i;
	int j;
	int x2_projection;
	int y2_projection;
	int x1_projection;
	int y1_projection;
	int zoom;
	int error;

	map = parse_map("test.fdf");
	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "test FDF");

	i = 0;
	j = 0;
	zoom = 20;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			x1_projection = (map.grid[i][j].x * zoom - map.grid[i][j].y * zoom)
				* cos(30 * M_PI / 180);
			y1_projection = (map.grid[i][j].x * zoom + map.grid[i][j].y * zoom)
				* sin(30 * M_PI / 180) - map.grid[i][j].z * zoom;
			x2_projection = (map.grid[i][j + 1].x * zoom - map.grid[i][j + 1].y
					* zoom) * cos(30 * M_PI / 180);
			y2_projection = (map.grid[i][j + 1].x * zoom + map.grid[i][j + 1].y
					* zoom) * sin(30 * M_PI / 180) - map.grid[i][j + 1].z
				* zoom;
			x1_projection += (800 - map.width * zoom) / 2;
			y1_projection += (600 / 2) - (map.height / 2);
			mlx_pixel_put(mlx, win, x1_projection, y1_projection,
				map.grid[i][j].color);
			j++;
		}
		i++;
	}
	mlx_loop(mlx);
	return (0);
}