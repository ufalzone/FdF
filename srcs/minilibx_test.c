/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:40:49 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/03 23:07:12 by ufalzone         ###   ########.fr       */
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

void	all_lines(t_fdf *fdf)
{
    int	i;
    int	j;
	    int x1_projection;
    int y1_projection;
    int x2_projection;
    int y2_projection;
    int	total_points;
    int	current_point;
    
    total_points = fdf->map.width * fdf->map.height;
    current_point = 0;
    
    ft_printf("\033[H\033[J");  // Efface le terminal
    ft_printf("Calcul des points en cours...\n");
    
    i = 0;
    while (i < fdf->map.height)
    {
        j = 0;
        while (j < fdf->map.width)
        {
            // Projection isométrique
            x1_projection = (fdf->map.grid[i][j].x * fdf->zoom - fdf->map.grid[i][j].y * fdf->zoom) * cos(fdf->angle_iso * M_PI / 180);
            y1_projection = (fdf->map.grid[i][j].x * fdf->zoom + fdf->map.grid[i][j].y * fdf->zoom) * sin(fdf->angle_iso * M_PI / 180) - fdf->map.grid[i][j].z / fdf->z_divisor * fdf->zoom;

            // Centrage de l'image
            x1_projection += (WEIGHT - fdf->map.width * fdf->zoom) / 2 + fdf->offset_x;
            y1_projection += (HEIGHT - fdf->map.height * fdf->zoom) / 2 + fdf->offset_y;

            // Tracé horizontal (vers le point à droite)
            if (j + 1 < fdf->map.width)
            {

                // Projection isométrique
                x2_projection = (fdf->map.grid[i][j + 1].x * fdf->zoom - fdf->map.grid[i][j + 1].y * fdf->zoom) * cos(fdf->angle_iso * M_PI / 180);
                y2_projection = (fdf->map.grid[i][j + 1].x * fdf->zoom + fdf->map.grid[i][j + 1].y * fdf->zoom) * sin(fdf->angle_iso * M_PI / 180) - fdf->map.grid[i][j + 1].z / fdf->z_divisor * fdf->zoom;

                // Centrage de l'image
                x2_projection += (WEIGHT - fdf->map.width * fdf->zoom) / 2 + fdf->offset_x;
                y2_projection += (HEIGHT - fdf->map.height * fdf->zoom) / 2 + fdf->offset_y;

                // Tracer la ligne horizontale
                trace_line(fdf->mlx, fdf->win, x1_projection, y1_projection, x2_projection, y2_projection, fdf->map.grid[i][j].color);
            }

            // Tracé vertical (vers le point en bas)
            if (i + 1 < fdf->map.height)
            {
                // Projection isométrique
                x2_projection = (fdf->map.grid[i + 1][j].x * fdf->zoom - fdf->map.grid[i + 1][j].y * fdf->zoom) * cos(fdf->angle_iso * M_PI / 180);
                y2_projection = (fdf->map.grid[i + 1][j].x * fdf->zoom + fdf->map.grid[i + 1][j].y * fdf->zoom) * sin(fdf->angle_iso * M_PI / 180) - fdf->map.grid[i + 1][j].z / fdf->z_divisor * fdf->zoom;

                // Centrage de l'image
                x2_projection += (WEIGHT - fdf->map.width * fdf->zoom) / 2 + fdf->offset_x;
                y2_projection += (HEIGHT - fdf->map.height * fdf->zoom) / 2 + fdf->offset_y;

                // Tracer la ligne verticale
                trace_line(fdf->mlx, fdf->win, x1_projection, y1_projection, x2_projection, y2_projection, fdf->map.grid[i][j].color);
            }
            j++;
        }
        i++;
    }
    ft_printf("\nRendu terminé !\n");
}


// int	deplacement(void *mlx, void *win, t_map map, int zoom)
// {
// 	mlx_hook(win, 2, 1L << 0, &key_hook, mlx);

// }

// Deplacement avec les touches
//Fleche gauche et A pour gauche
//Fleche droite et D pour droite
//Fleche haut et W pour haut
//Fleche bas et S pour bas
//Fleche + pour zoom
//Fleche - pour dezoom
//Angle Projection Isométrique = 1 = 2D
//Angle Projection Isométrique = 0 = 3D

int	deplacement(int keycode, t_fdf *fdf)
{
	if (keycode == 65361 || keycode == 97) // Flèche gauche
		fdf->offset_x += 50;
	else if (keycode == 65363 || keycode == 100) // Flèche droite
		fdf->offset_x -= 50;
	else if (keycode == 65362 || keycode == 119) // Flèche haut
		fdf->offset_y += 50;
	else if (keycode == 65364 || keycode == 115) // Flèche bas
		fdf->offset_y -= 50;
	else if (keycode == 61)
		fdf->zoom += 1;
	else if (keycode == 45)
		fdf->zoom -= 1;
	else if (keycode == 49) // Touche '1'
		fdf->angle_iso = 0; // Angle isométrique pour 2D
	else if (keycode == 50) // Touche '2'
		fdf->angle_iso = 30; // Angle isométrique pour 3D
	else if (keycode == 111) // Touche 'o'
	{
		if (fdf->z_divisor > 1)
			fdf->z_divisor -= 1;
	}
	else if (keycode == 112) // Touche 'p'
		fdf->z_divisor += 1;
	else if (keycode == 122) // Touche 'z'
		fdf->angle_z += 1; // Incrémente l'angle de rotation autour de l'axe Z
	else if (keycode == 121) // Touche 'y'
		fdf->angle_y += 1; // Incrémente l'angle de rotation autour de l'axe Y
	else if (keycode == 120) // Touche 'x'
		fdf->angle_x += 1; // Incrémente l'angle de rotation autour de l'axe X
	else if (keycode == 65307) // Échap pour quitter
		exit(0);
	// Efface la fenêtre et redessine tout
	mlx_clear_window(fdf->mlx, fdf->win);
	all_lines(fdf);
	return (0);
}

int	zoom(int keycode, int x, int y, t_fdf *fdf)
{
	x = 0;
	y = 0;
	if (keycode == 4)
		fdf->zoom += 1;
	else if (keycode == 5)
		fdf->zoom -= 1;
	mlx_clear_window(fdf->mlx, fdf->win);
	all_lines(fdf);
	return (0);
}
int	mouse_pressed(int button, int x, int y, t_fdf *fdf)
{
	if (button == 3) // Clic droit
	{
		fdf->is_right_clicked = 1;
		fdf->last_x = x;
		fdf->last_y = y;
	}
	else if (button == 4) // Molette vers le haut
	{
		fdf->zoom += 2;
		mlx_clear_window(fdf->mlx, fdf->win);
		all_lines(fdf);
	}
	else if (button == 5) // Molette vers le bas
	{
		fdf->zoom -= 1;
		mlx_clear_window(fdf->mlx, fdf->win);
		all_lines(fdf);
	}
	return (0);
}

int	mouse_released(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 3)
		fdf->is_right_clicked = 0;
	return (0);
}

int	deplacement_mouse(int x, int y, t_fdf *fdf)
{
	if (fdf->is_right_clicked == 1)
	{
		fdf->offset_x += (x - fdf->last_x);
		fdf->offset_y += (y - fdf->last_y);

		mlx_clear_window(fdf->mlx, fdf->win);
		all_lines(fdf);
		fdf->last_x = x;
		fdf->last_y = y;	
	}
	return (0);
}



int	main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac != 2)
		return (ft_printf("Utilisation: ./fdf <nom du fichier>"));
	fdf.map = parse_map(av[1]);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, WEIGHT, HEIGHT, "test FDF");
	fdf.zoom = 10;
	fdf.offset_x = 0;
	fdf.offset_y = 0;
	fdf.is_right_clicked = 0;
	fdf.angle_iso = 30;
	fdf.z_divisor = 1;
	fdf.angle_x = 0;
	fdf.angle_y = 0;
	fdf.angle_z = 0;
	all_lines(&fdf);
	mlx_key_hook(fdf.win, &deplacement, &fdf);        
		// Deplacement avec les touches
	mlx_hook(fdf.win, 4, (1L<<2), &mouse_pressed, &fdf);     // Clic souris pressé
	mlx_hook(fdf.win, 5, (1L<<3), &mouse_released, &fdf);    // Clic souris relâché
	mlx_hook(fdf.win, 6, (1L<<6), &deplacement_mouse, &fdf); // Mouvement de la souris
	mlx_loop(fdf.mlx);
	return (0);
}
