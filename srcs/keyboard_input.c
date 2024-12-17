/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:58:39 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/17 03:04:55 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdlib.h>

#define ROTATION_SPEED 5

/* Controles clavier:
**
** Déplacements:
** ← ou A (65361/97)  : Déplacement vers la gauche
** → ou D (65363/100) : Déplacement vers la droite
** ↑ ou W (65362/119) : Déplacement vers le haut
** ↓ ou S (65364/115) : Dplacement vers le bas
**
** Zoom:
** + (61) : Zoom avant
** - (45) : Zoom arrière
**
** Hauteur (axe Z):
** P (112)     : Augmente la hauteur
** O/Q (111/113) : Diminue la hauteur
**
** Rotation:
** X (120) : Rotation autour de l'axe X
** Y (121) : Rotation autour de l'axe Y
** Z (122) : Rotation autour de l'axe Z
**
** Projection:
** 1 (49) : Vue parallèle (angle_iso = 0)
** 2 (50) : Vue isométrique (angle_iso = 30)
**
** Contrôles:
** R (114)    : Réinitialise tous les paramètres
** ESC (65307) : Ferme la fenêtre
*/

// Gere les mouvements avec les fleches et WASD
static void	key_movement(int keycode, t_fdf *fdf)
{
	if (keycode == 65361 || keycode == 97)
		fdf->offset_x += 50;
	else if (keycode == 65363 || keycode == 100)
		fdf->offset_x -= 50;
	else if (keycode == 65362 || keycode == 119)
		fdf->offset_y += 50;
	else if (keycode == 65364 || keycode == 115)
		fdf->offset_y -= 50;
}

// Gere le zoom et les modifications de l'axe z
static void	key_zoom_and_z(int keycode, t_fdf *fdf)
{
	if (keycode == 61)
		fdf->zoom += 1;
	else if (keycode == 45)
		fdf->zoom -= 1;
	else if (keycode == 112)
		fdf->z_divisor += 1;
	else if (keycode == 49)
	{
		fdf->projection_type = 0;
		fdf->angle_iso = 0;
	}
	else if (keycode == 50)
	{
		fdf->projection_type = 0;
		fdf->angle_iso = 30;
	}
	else if (keycode == 51)
	{
		fdf->projection_type = 1;
		fdf->angle_iso = 45;
	}
	else if (keycode == 113 || keycode == 111)
		if (fdf->z_divisor > 1)
			fdf->z_divisor -= 1;
}

// Gere les projections et les rotations
static void	key_rotation(int keycode, t_fdf *fdf)
{
	if (keycode == 120)
		fdf->angle_x += ROTATION_SPEED;
	else if (keycode == 121)
		fdf->angle_y += ROTATION_SPEED;
	else if (keycode == 122)
		fdf->angle_z += ROTATION_SPEED;
	if (fdf->angle_x > 360)
		fdf->angle_x = 0;
	if (fdf->angle_y > 360)
		fdf->angle_y = 0;
	if (fdf->angle_z > 360)
		fdf->angle_z = 0;
}

// Réinitialise tous les paramètres
static void	key_reset(t_fdf *fdf)
{
	fdf->offset_x = (WEIGHT / 2) - ((fdf->map.width * fdf->zoom) / 2);
	fdf->offset_y = (HEIGHT / 2) - ((fdf->map.height * fdf->zoom) / 2);
	fdf->zoom = calculate_optimal_zoom(fdf->map.width, fdf->map.height);
	fdf->z_divisor = 1;
	fdf->angle_x = 0;
	fdf->angle_y = 0;
	fdf->angle_z = 0;
	fdf->projection_type = 0;
	fdf->angle_iso = 30;
}

int	key_input(int keycode, t_fdf *fdf)
{
	if (keycode == 114)
		key_reset(fdf);
	key_movement(keycode, fdf);
	key_zoom_and_z(keycode, fdf);
	key_rotation(keycode, fdf);
	if (keycode == 65307)
		close_window(fdf);
	draw_all_lines(fdf);
	return (0);
}
