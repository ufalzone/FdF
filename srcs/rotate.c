/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:35:37 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/06 18:01:54 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Rotation en X
void	rotate_x(t_fdf *fdf, int *x, int *y, int *z)
{
	double	y_temp;
	double	z_temp;

	(void)x;
	y_temp = *y;
	z_temp = *z;
	*y = y_temp * cos(fdf->angle_x) + z_temp * sin(fdf->angle_x);
	*z = -y_temp * sin(fdf->angle_x) + z_temp * cos(fdf->angle_x);
}
// Rotation en Y
void	rotate_y(t_fdf *fdf, int *x, int *y, int *z)
{
	double	x_temp;
	double	z_temp;

	(void)y;
	x_temp = *x;
	z_temp = *z;
	*x = x_temp * cos(fdf->angle_y) - z_temp * sin(fdf->angle_y);
	*z = x_temp * sin(fdf->angle_y) + z_temp * cos(fdf->angle_y);
}
// Rotation en Z
void	rotate_z(t_fdf *fdf, int *x, int *y, int *z)
{
	double	y_temp;
	double	x_temp;

	(void)z;
	y_temp = *y;
	x_temp = *x;
	*y = y_temp * cos(fdf->angle_z) - x_temp * sin(fdf->angle_z);
	*x = y_temp * sin(fdf->angle_z) + x_temp * cos(fdf->angle_z);
}
