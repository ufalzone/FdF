/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:40:49 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/06 18:02:06 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/mlx.h"

static void	init_fdf(t_fdf *fdf, char **av)
{
	fdf->map = parse_map(av[1]);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WEIGHT, HEIGHT, "test FDF");
	fdf->zoom = 10;
	fdf->offset_x = 0;
	fdf->offset_y = 0;
	fdf->is_right_clicked = 0;
	fdf->angle_iso = 30;
	fdf->z_divisor = 1;
	fdf->angle_x = 0;
	fdf->angle_y = 0;
	fdf->angle_z = 0;
	fdf->img = mlx_new_image(fdf->mlx, WEIGHT, HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
			&fdf->size_line, &fdf->endian);
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
