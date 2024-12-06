/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:54:03 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/06 18:15:28 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Calcule l'adresse de la pixel et le colorie
static void	addr_pixel_calculation(t_fdf *fdf, int x0, int y0, int color)
{
	char	*addr_pixel;

	if (x0 >= 0 && x0 < WEIGHT && y0 >= 0 && y0 < HEIGHT)
	{
		addr_pixel = fdf->addr + (y0 * fdf->size_line) + (x0
				* (fdf->bits_per_pixel / 8));
		*(unsigned int *)addr_pixel = color;
	}
}
    
// Pente raide
void	trace_ligne_high(t_fdf *fdf, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	xi;
	int	error;

	dx = x1 - x0;
	dy = y1 - y0;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	error = 2 * dx - dy;
	while (y0 <= y1)
	{
		addr_pixel_calculation(fdf, x0, y0, color);
		if (error > 0)
		{
			x0 += xi;
			error = error - 2 * dy;
		}
		error = error + 2 * dx;
		y0++;
	}
}

// Pente douce
void	trace_ligne_low(t_fdf *fdf, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	yi;
	int	error;

	dx = x1 - x0;
	dy = y1 - y0;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	error = 2 * dy - dx;
	while (x0 <= x1)
	{
		addr_pixel_calculation(fdf, x0, y0, color);
		if (error > 0)
		{
			y0 += yi;
			error = error - 2 * dx;
		}
		error = error + 2 * dy;
		x0++;
	}
}

// Determine la pente de la ligne et trace la ligne en fonction de la pente
void	trace_line(t_fdf *fdf, int x0, int y0, int x1, int y1, int color)
{
	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1)
			trace_ligne_low(fdf, x1, y1, x0, y0, color);
		else
			trace_ligne_low(fdf, x0, y0, x1, y1, color);
	}
	else
	{
		if (y0 > y1)
			trace_ligne_high(fdf, x1, y1, x0, y0, color);
		else
			trace_ligne_high(fdf, x0, y0, x1, y1, color);
	}
}
