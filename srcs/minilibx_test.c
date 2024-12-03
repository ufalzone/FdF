/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:40:49 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/03 14:45:07 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/mlx.h"
#include <math.h>

// quand dy > dx, pente raide
void	trace_ligne_high(void *mlx, void *win, int x0, int y0, int x1, int y1,
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
	while (y0 <= y1)
	{
		mlx_pixel_put(mlx, win, x0, y0, color);
		if (D > 0)
		{
			x0 += xi;
			D = D - 2 * dy;
		}
		D = D + 2 * dx;
		y0++;
	}
}
// Pente douce
void	trace_ligne_low(void *mlx, void *win, int x0, int y0, int x1, int y1,
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
	while (x0 <= x1)
	{
		mlx_pixel_put(mlx, win, x0, y0, color);
		if (D > 0)
		{
			y0 += yi;
			D = D - 2 * dx;
		}
		D = D + 2 * dy;
		x0++;
	}
}

void	trace_line(void *mlx, void *win, int x0, int y0, int x1, int y1,
		int color)
{
	int	temp;

	if (abs(y1 - y0) < abs(x1 - x0)) // Pente douce
	{
		// Si x0 > x1, on echange les points
		if (x0 > x1)
		{
			temp = x0;
			x0 = x1;
			x1 = temp;
			temp = y0;
			y0 = y1;
			y1 = temp;
		}
		trace_ligne_low(mlx, win, x0, y0, x1, y1, color);
	}
	// Pente raide
	else
	{
		// Si y0 > y1, on echange les points
		if (y0 > y1)
		{
			temp = x0;
			x0 = x1;
			x1 = temp;
			temp = y0;
			y0 = y1;
			y1 = temp;
		}
		trace_ligne_high(mlx, win, x0, y0, x1, y1, color);
	}
}
void	all_lines(void *mlx, void *win, t_map map, int zoom)
{
	int	i;
	int	j;
	int	x1_projection;
	int	y1_projection;
	int	x2_projection;
	int	y2_projection;

	i = 0;
	j = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			// Tracé horizontal (vers le point à droite)
			if (j + 1 < map.width)
			{
				x1_projection = (map.grid[i][j].x * zoom - map.grid[i][j].y
						* zoom) * cos(30 * M_PI / 180);
				y1_projection = (map.grid[i][j].x * zoom + map.grid[i][j].y
						* zoom) * sin(30 * M_PI / 180) - map.grid[i][j].z
					* zoom;
				x2_projection = (map.grid[i][j + 1].x * zoom - map.grid[i][j
						+ 1].y * zoom) * cos(30 * M_PI / 180);
				y2_projection = (map.grid[i][j + 1].x * zoom + map.grid[i][j
						+ 1].y * zoom) * sin(30 * M_PI / 180) - map.grid[i][j
					+ 1].z * zoom;
				x1_projection += (800 - map.width * zoom) / 2;
				y1_projection += (600 - map.height * zoom) / 2;
				x2_projection += (800 - map.width * zoom) / 2;
				y2_projection += (600 - map.height * zoom) / 2;
				trace_line(mlx, win, x1_projection, y1_projection,
					x2_projection, y2_projection, map.grid[i][j].color);
			}
			// Tracé vertical (vers le point en bas)
			if (i + 1 < map.height)
			{
				x1_projection = (map.grid[i][j].x * zoom - map.grid[i][j].y
						* zoom) * cos(30 * M_PI / 180);
				y1_projection = (map.grid[i][j].x * zoom + map.grid[i][j].y
						* zoom) * sin(30 * M_PI / 180) - map.grid[i][j].z
					* zoom;
				x2_projection = (map.grid[i + 1][j].x * zoom - map.grid[i
						+ 1][j].y * zoom) * cos(30 * M_PI / 180);
				y2_projection = (map.grid[i + 1][j].x * zoom + map.grid[i
						+ 1][j].y * zoom) * sin(30 * M_PI / 180) - map.grid[i
					+ 1][j].z * zoom;
				x1_projection += (800 - map.width * zoom) / 2;
				y1_projection += (600 - map.height * zoom) / 2;
				x2_projection += (800 - map.width * zoom) / 2;
				y2_projection += (600 - map.height * zoom) / 2;
				trace_line(mlx, win, x1_projection, y1_projection,
					x2_projection, y2_projection, map.grid[i][j].color);
			}
			j++;
		}
		i++;
	}
}

// int	deplacement(void *mlx, void *win, t_map map, int zoom)
// {
// 	mlx_hook(win, 2, 1L << 0, &key_hook, mlx);

// }

int	main(int ac, char **av)
{
	void	*mlx;
	void	*win;
	t_map	map;
	int		zoom;

	if (ac != 2)
		return (ft_printf("Utilisation: ./fdf <nom du fichier>"));
	map = parse_map(av[1]);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "test FDF");
	zoom = 1;
	all_lines(mlx, win, map, zoom);
	mlx_loop(mlx);
	return (0);
}
