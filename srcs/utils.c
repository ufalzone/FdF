/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:42:38 by ufalzone          #+#    #+#             */
/*   Updated: 2024/12/08 18:58:10 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <unistd.h>

int	close_window(void)
{
	exit(0);
}

int	error_close_window(int error, char *filename)
{
	if (error == 1)
		ft_printf("\033[31m❌ Erreur: Nom de fichier invalide\033[0m\n");
	else if (error == 2)
		ft_printf("\033[31m❌ Erreur: '%s' est un dossier\033[0m\n", filename);
	else if (error == 3)
		ft_printf("\033[31m❌ Erreur: Impossible d'ouvrir '%s'\033[0m\n",
			filename);
	else if (error == 4)
		ft_printf("\033[31m❌ Erreur: Dimensions invalides\033[0m\n");
	else if (error == 5)
		ft_printf("\033[31m❌ Erreur: Utilisation ./fdf [map.fdf]\033[0m\n");
	exit(1);
}
