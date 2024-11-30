/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 01:13:42 by ufalzone          #+#    #+#             */
/*   Updated: 2024/11/13 14:08:03 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*schar;

	i = 0;
	schar = (unsigned char *)s;
	while (i < n)
	{
		schar[i] = 0;
		i++;
	}
}
