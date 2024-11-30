/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:32:47 by ufalzone          #+#    #+#             */
/*   Updated: 2024/11/14 22:33:59 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 0 	Entrée standard 	STDIN_FILENO 	stdin
// 1 	Sortie standard 	STDOUT_FILENO 	stdout
// 2 	Erreur standard 	STDERR_FILENO 	stderr

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
