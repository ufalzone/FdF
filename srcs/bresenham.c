/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:54:03 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/07 17:34:52 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Calcule l'adresse du pixel et le colorie
static void	addr_pixel_calculation(t_fdf *fdf, t_point *point)
{
	char	*addr_pixel;

	if (point->x >= 0 && point->x < WEIGHT && point->y >= 0
		&& point->y < HEIGHT)
	{
		addr_pixel = fdf->addr + (point->y * fdf->size_line) + (point->x
				* (fdf->bits_per_pixel / 8));
		*(unsigned int *)addr_pixel = point->color;
	}
}

// Pente raide
static void	trace_ligne_high(t_fdf *fdf, t_point start, t_point end)
{
	int	dx;
	int	dy;
	int	xi;
	int	error;

	dx = end.x - start.x;
	dy = end.y - start.y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	error = 2 * dx - dy;
	while (start.y <= end.y)
	{
		addr_pixel_calculation(fdf, &start);
		if (error > 0)
		{
			start.x += xi;
			error -= 2 * dy;
		}
		error = error + 2 * dx;
		start.y++;
	}
}

// Pente douce
static void	trace_ligne_low(t_fdf *fdf, t_point start, t_point end)
{
	int	dx;
	int	dy;
	int	yi;
	int	error;

	dx = end.x - start.x;
	dy = end.y - start.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	error = 2 * dy - dx;
	while (start.x <= end.x)
	{
		addr_pixel_calculation(fdf, &start);
		if (error > 0)
		{
			start.y += yi;
			error = error - 2 * dx;
		}
		error = error + 2 * dy;
		start.x++;
	}
}

// Determine la pente de la ligne et trace la ligne en fonction de la pente
void	trace_line(t_fdf *fdf, t_point start, t_point end)
{
	if (abs(end.y - start.y) < abs(end.x - start.x))
	{
		if (start.x > end.x)
			trace_ligne_low(fdf, end, start);
		else
			trace_ligne_low(fdf, start, end);
	}
	else
	{
		if (start.y > end.y)
			trace_ligne_high(fdf, end, start);
		else
			trace_ligne_high(fdf, start, end);
	}
}
