/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufalzone <ufalzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:26:10 by ufalzone          #+#    #+#             */
/*   Updated: 2024/11/17 00:50:39 by ufalzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char s, char c)
{
	if (c == s)
		return (1);
	return (0);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	compteur;

	compteur = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && is_charset(s[i], c))
			i++;
		if (s[i] != '\0')
			compteur++;
		while (s[i] && !is_charset(s[i], c))
			i++;
	}
	return (compteur);
}

static int	ft_wordlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && !is_charset(s[i], c))
		i++;
	return (i);
}

static char	*ft_worddup(char const *s, char c)
{
	int		i;
	char	*tab;
	int		size;

	i = 0;
	size = ft_wordlen(s, c);
	tab = malloc(sizeof(char) * size + 1);
	if (!tab)
		return (NULL);
	while (i < size)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**all;
	int		j;
	int		i;
	int		nbr_mots;

	nbr_mots = count_words(s, c);
	all = malloc(sizeof(char *) * (nbr_mots + 1));
	if (!all)
		return (NULL);
	all[nbr_mots] = 0;
	i = 0;
	j = 0;
	while (i < nbr_mots)
	{
		while (s[j] && is_charset(s[j], c))
			j++;
		all[i] = ft_worddup(&s[j], c);
		if (all[i] == NULL)
			return (NULL);
		while (s[j] && !is_charset(s[j], c))
			j++;
		i++;
	}
	return (all);
}

// #include <stdio.h>

// int	main(int ac, char **av)
// {
// 	char	**tab;
// 	int		i;

// 	if (ac != 2)
// 		return (0);
// 	tab = ft_split(av[1], 's');
// 	i = 0;
// 	while (tab[i])
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// 	return (0);
// }