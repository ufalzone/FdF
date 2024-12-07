/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:35:37 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/07 17:37:45 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Rotation en X
void	rotate_x(t_fdf *fdf, t_point *point)
{
	double	y_temp;
	double	z_temp;
	double	radiant_angle;

	radiant_angle = fdf->angle_x * M_PI / 180.0;
	point->x -= fdf->center_x;
	point->y -= fdf->center_y;
	point->z -= fdf->center_z;
	y_temp = point->y;
	z_temp = point->z;
	point->y = y_temp * cos(radiant_angle) + z_temp * sin(radiant_angle);
	point->z = -y_temp * sin(radiant_angle) + z_temp * cos(radiant_angle);
	point->x += fdf->center_x;
	point->y += fdf->center_y;
	point->z += fdf->center_z;
}

// Rotation en Y
void	rotate_y(t_fdf *fdf, t_point *point)
{
	double	x_temp;
	double	z_temp;
	double	radiant_angle;

	radiant_angle = fdf->angle_y * M_PI / 180.0;
	point->x -= fdf->center_x;
	point->y -= fdf->center_y;
	point->z -= fdf->center_z;
	x_temp = point->x;
	z_temp = point->z;
	point->x = x_temp * cos(radiant_angle) - z_temp * sin(radiant_angle);
	point->z = x_temp * sin(radiant_angle) + z_temp * cos(radiant_angle);
	point->x += fdf->center_x;
	point->y += fdf->center_y;
	point->z += fdf->center_z;
}

// Rotation en Z
void	rotate_z(t_fdf *fdf, t_point *point)
{
	double	x_temp;
	double	y_temp;
	double	radiant_angle;

	radiant_angle = fdf->angle_z * M_PI / 180.0;
	point->x -= fdf->center_x;
	point->y -= fdf->center_y;
	point->z -= fdf->center_z;
	x_temp = point->x;
	y_temp = point->y;
	point->x = x_temp * cos(radiant_angle) - y_temp * sin(radiant_angle);
	point->y = x_temp * sin(radiant_angle) + y_temp * cos(radiant_angle);
	point->x += fdf->center_x;
	point->y += fdf->center_y;
	point->z += fdf->center_z;
}
