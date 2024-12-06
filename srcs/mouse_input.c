/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:54:34 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/06 18:02:42 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Gere le clic droit et le zoom de la moulette
int	mouse_pressed(int button, int x, int y, t_fdf *fdf)
{
	if (button == 3)
	{
		fdf->is_right_clicked = 1;
		fdf->last_x = x;
		fdf->last_y = y;
	}
	else if (button == 4)
		fdf->zoom += 2;
	else if (button == 5)
		fdf->zoom -= 1;
	draw_all_lines(fdf);
	return (0);
}

// Gere le relachement du clic droit
int	mouse_released(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 3)
		fdf->is_right_clicked = 0;
	return (0);
}

// Calcule le deplacement de la souris pour le clic droit
int	deplacement_mouse(int x, int y, t_fdf *fdf)
{
	if (fdf->is_right_clicked == 1)
	{
		fdf->offset_x += (x - fdf->last_x);
		fdf->offset_y += (y - fdf->last_y);
		draw_all_lines(fdf);
		fdf->last_x = x;
		fdf->last_y = y;
	}
	return (0);
}
