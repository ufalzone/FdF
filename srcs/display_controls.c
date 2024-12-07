/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_controls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:45:12 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/07 17:48:42 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	draw_background(t_fdf *fdf)
{
	int		x;
	int		y;
	int		width;
	int		height;
	char	*pixel;

	width = 250;
	height = 300;
	y = 10;
	while (y < height)
	{
		x = 10;
		while (x < width)
		{
			pixel = fdf->addr + (y * fdf->size_line + x
					* (fdf->bits_per_pixel / 8));
			*(unsigned int *)pixel = 0x303030;
			x++;
		}
		y++;
	}
}

void	display_controls2(t_fdf *fdf, int y_pos, int x_pos)
{
	mlx_string_put(fdf->mlx, fdf->win, x_pos, y_pos += 20, 0xFFFFFF,
		"Z : Rotation axe Z");
	mlx_string_put(fdf->mlx, fdf->win, x_pos, y_pos += 20, 0xFFFFFF,
		"1 : Vue Plate");
	mlx_string_put(fdf->mlx, fdf->win, x_pos, y_pos += 20, 0xFFFFFF,
		"2 : Vue isometrique");
	mlx_string_put(fdf->mlx, fdf->win, x_pos, y_pos += 20, 0xFFFFFF,
		"3 : Vue parallele");
	mlx_string_put(fdf->mlx, fdf->win, x_pos, y_pos += 20, 0xFFFFFF,
		"R : Reinitialiser la vue");
}

void	display_controls(t_fdf *fdf)
{
	int	y_pos;
	int	x_pos;

	draw_background(fdf);
	y_pos = 30;
	x_pos = 20;
	mlx_string_put(fdf->mlx, fdf->win, x_pos, y_pos, 0xFFFFFF,
		"=== CONTROLES ===");
	mlx_string_put(fdf->mlx, fdf->win, x_pos, y_pos += 25, 0xFFFFFF,
		"ESC : Quitter");
	mlx_string_put(fdf->mlx, fdf->win, x_pos, y_pos += 20, 0xFFFFFF,
		"Fleches/WASD : Deplacer la vue");
	mlx_string_put(fdf->mlx, fdf->win, x_pos, y_pos += 20, 0xFFFFFF,
		"+ / - : Zoom");
	mlx_string_put(fdf->mlx, fdf->win, x_pos, y_pos += 20, 0xFFFFFF,
		"P : Augmenter hauteur");
	mlx_string_put(fdf->mlx, fdf->win, x_pos, y_pos += 20, 0xFFFFFF,
		"O/Q : Diminuer hauteur");
	mlx_string_put(fdf->mlx, fdf->win, x_pos, y_pos += 20, 0xFFFFFF,
		"X : Rotation axe X");
	mlx_string_put(fdf->mlx, fdf->win, x_pos, y_pos += 20, 0xFFFFFF,
		"Y : Rotation axe Y");
	display_controls2(fdf, y_pos, x_pos);
}
