/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:52:29 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/06 18:29:28 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	clear_image(t_fdf *fdf, int color)
{
	int		x;
	int		y;
	char	*pixel_addr;

	y = 0;
	mlx_clear_window(fdf->mlx, fdf->win);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WEIGHT)
		{
			pixel_addr = fdf->addr + (y * fdf->size_line) + (x
					* (fdf->bits_per_pixel / 8));
			*(unsigned int *)pixel_addr = color;
			x++;
		}
		y++;
	}
}

static void	calcul_projection(t_fdf *fdf, int i, int j, t_coord *coord)
{
	int	x;
	int	y;
	int	z;

	x = fdf->map.grid[i][j].x;
	y = fdf->map.grid[i][j].y;
	z = fdf->map.grid[i][j].z;
	rotate_x(fdf, &x, &y, &z);
	rotate_y(fdf, &x, &y, &z);
	rotate_z(fdf, &x, &y, &z);
	coord->x0 = (x * fdf->zoom - y * fdf->zoom) * cos(fdf->angle_iso * M_PI
			/ 180);
	coord->y0 = (x * fdf->zoom + y * fdf->zoom) * sin(fdf->angle_iso * M_PI
			/ 180) - (int)(z / fdf->z_divisor * fdf->zoom);
	coord->x0 += (WEIGHT - fdf->map.width * fdf->zoom) / 2 + fdf->offset_x;
	coord->y0 += (HEIGHT - fdf->map.height * fdf->zoom) / 2 + fdf->offset_y;
}

static int	check_line_valid(t_fdf *fdf, int i, int j, t_coord *coord)
{
	if (coord->x1 < 0 || coord->x1 >= WEIGHT || coord->y1 < 0
		|| coord->y1 >= HEIGHT)
		return (0);
	if (direction == 0)
	{
		return (j + 1 < fdf->map.width && fdf->map.grid[i] && fdf->map.grid[i][j
			+ 1].x >= 0);
	}
	else
	{
		return (i + 1 < fdf->map.height && fdf->map.grid[i + 1]
			&& fdf->map.grid[i + 1][j].x >= 0);
	}
}

static void	draw_point_connections(t_fdf *fdf, int i, int j)
{
	t_coord	coord;

	calcul_projection(fdf, i, j, &coord);
	if (check_line_valid(fdf, i, j, 0, coord.x1, coord.y1))
	{
		calcul_projection(fdf, i, j + 1, &coord.x1, &coord.y1);
		trace_line(fdf, coord.x0, coord.y0, coord.x1, coord.y1, fdf->map.grid[i][j].color);
	}
	if (check_line_valid(fdf, i, j, 1, coord.x1, coord.y1))
	{
		calcul_projection(fdf, i + 1, j, &coord.x1, &coord.y1);
		trace_line(fdf, coord.x0, coord.y0, coord.x1, coord.y1, fdf->map.grid[i][j].color);
	}
}

void	draw_all_lines(t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	clear_image(fdf, 000000);
	while (++i < fdf->map.height)
	{
		j = -1;
		while (++j < fdf->map.width)
			draw_point_connections(fdf, i, j);
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
