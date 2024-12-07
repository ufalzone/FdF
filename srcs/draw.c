/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:52:29 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/07 17:45:27 by ufalzone         ###   ########.fr       */
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

// Calcul de la projection - Centrage - Rotation - Projection isométrique
static void	calcul_projection(t_fdf *fdf, int i, int j, t_point *point)
{
	int	temp_x;
	int	temp_y;

	point->x = j * fdf->zoom;
	point->y = i * fdf->zoom;
	point->z = fdf->map.grid[i][j].z * fdf->zoom;
	rotate_x(fdf, point);
	rotate_y(fdf, point);
	rotate_z(fdf, point);
	temp_x = point->x;
	temp_y = point->y;
	if (fdf->projection_type == 0)
	{
		point->x = (temp_x - temp_y) * cos(fdf->angle_iso * M_PI / 180);
		point->y = (int)(temp_x + temp_y) *sin(fdf->angle_iso * M_PI / 180)
			- (float)point->z / fdf->z_divisor;
	}
	else if (fdf->projection_type == 1)
	{
		point->x = temp_x - point->z * cos(fdf->angle_iso * M_PI / 180);
		point->y = temp_y - point->z * sin(fdf->angle_iso * M_PI / 180);
	}
	point->x += (WEIGHT - fdf->map.width * fdf->zoom) / 2 + fdf->offset_x;
	point->y += (HEIGHT - fdf->map.height * fdf->zoom) / 2 + fdf->offset_y;
	point->color = fdf->map.grid[i][j].color;
}

static void	draw_point_connections(t_fdf *fdf, int i, int j)
{
	t_point	start;
	t_point	end;

	calcul_projection(fdf, i, j, &start);
	if (i + 1 < fdf->map.height)
	{
		calcul_projection(fdf, i + 1, j, &end);
		trace_line(fdf, start, end);
	}
	if (j + 1 < fdf->map.width)
	{
		calcul_projection(fdf, i, j + 1, &end);
		trace_line(fdf, start, end);
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
	display_controls(fdf);
}
