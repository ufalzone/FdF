/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:40:49 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/07 17:10:48 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/mlx.h"

int	calculate_optimal_zoom(int map_width, int map_height)
{
	int	zoom_width;
	int	zoom_height;
	int	zoom;

	zoom_width = (WEIGHT - 400) / map_width;
	zoom_height = (HEIGHT - 400) / map_height;
	if (zoom_width < zoom_height)
		zoom = zoom_width;
	else
		zoom = zoom_height;
	if (zoom < 1)
		zoom = 1;
	return (zoom);
}

static void	init_fdf(t_fdf *fdf, char **av)
{
	fdf->map = parse_map(av[1]);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WEIGHT, HEIGHT, "FDF - ufalzone");
	fdf->zoom = calculate_optimal_zoom(fdf->map.width, fdf->map.height);
	fdf->offset_x = (WEIGHT / 3) - ((fdf->map.width * fdf->zoom) / 2);
	fdf->offset_y = (HEIGHT / 3) - ((fdf->map.height * fdf->zoom) / 2);
	fdf->is_right_clicked = 0;
	fdf->angle_iso = 45;
	fdf->z_divisor = 1;
	fdf->angle_x = 0;
	fdf->angle_y = 0;
	fdf->angle_z = 0;
	fdf->img = mlx_new_image(fdf->mlx, WEIGHT, HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
			&fdf->size_line, &fdf->endian);
	fdf->center_x = (fdf->map.width * fdf->zoom) / 2.0;
	fdf->center_y = (fdf->map.height * fdf->zoom) / 2.0;
	fdf->center_z = (fdf->map.z_max * fdf->zoom) / 2.0;
	fdf->projection_type = 1;
}

static void	init_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, &key_input, fdf);
	mlx_hook(fdf->win, 4, (1L << 2), &mouse_pressed, fdf);
	mlx_hook(fdf->win, 5, (1L << 3), &mouse_released, fdf);
	mlx_hook(fdf->win, 6, (1L << 6), &deplacement_mouse, fdf);
	mlx_hook(fdf->win, 17, 0, &close_window, NULL);
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac != 2)
		return (ft_printf("Utilisation: ./fdf <nom du fichier>"));
	init_fdf(&fdf, av);
	draw_all_lines(&fdf);
	init_hooks(&fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
