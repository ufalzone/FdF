/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:40:49 by ufalzone          #+#    #+#             */
/*   Updated: 2024/11/30 19:07:16 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/mlx.h"
#include <math.h>

// quand dy > dx, pente raide
void	trace_ligne_high(void *mlx, void *win, int x0, int x1, int y0, int y1,
		int color)
{
	int dx; // distance horizontale
	int dy; // distance verticale
	int xi; // mouvement
	int D;  // delta
	dx = x1 - x0;
	dy = y1 - y0;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	D = 2 * dx - dy;
	while (y0 != y1)
	{
		mlx_pixel_put(mlx, win, x0, y0, color);
		if (D > 0)
		{
			x0 += xi;
			D = D + 2 * (dx - dy);
		}
		else
			D = D + 2 * dx;
		y0++;
	}
}
void	trace_ligne_low(void *mlx, void *win, int x0, int x1, int y0, int y1,
		int color)
{
	int	dx;
	int	dy;
	int	yi;
	int	D;

	dx = x1 - x0;
	dy = y1 - y0;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	D = 2 * dy - dx;
	while (x0 != x1)
	{
		mlx_pixel_put(mlx, win, x0, y0, color);
		if (D > 0)
		{
			y0 += yi;
			D = D + 2 * (dy - dx);
		}
		else
			D = D + 2 * dy;
		x0++;
	}
}

void	trace_line(void *mlx, void *win, int x0, int y0, int x1, int y1,
		int color)
{
	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1)
			trace_ligne_low(mlx, win, x1, x0, y1, y0, color);
		else
			trace_ligne_low(mlx, win, x0, x1, y0, y1, color);
	}
	else
	{
		if (y0 > y1)
			trace_ligne_high(mlx, win, x0, x1, y0, y1, color);
		else
			trace_ligne_high(mlx, win, x1, x0, y1, y0, color);
	}
}

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

	map = parse_map("test.fdf");
	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "test FDF");

	i = 0;
	j = 0;
	zoom = 10;
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
			y1_projection += (600 - map.height * zoom) / 2;
			x2_projection += (800 - map.width * zoom) / 2;
			y2_projection += (600 - map.height * zoom) / 2;

			mlx_pixel_put(mlx, win, x1_projection, y1_projection,
				map.grid[i][j].color);
			trace_line(mlx, win, x1_projection, y1_projection, x2_projection,
				y2_projection, map.grid[i][j].color);
			j++;
		}
		i++;
	}
	mlx_loop(mlx);
	return (0);
}
