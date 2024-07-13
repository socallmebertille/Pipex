/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:36:04 by saberton          #+#    #+#             */
/*   Updated: 2024/07/12 14:37:46 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_count(const char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
		if (str[i] == '\0')
			return (count);
		else
			i++;
	}
	return (count);
}

static void	free_tab(char **tab, int count)
{
	while (count >= 0)
	{
		free(tab[count]);
		count--;
	}
	free(tab);
}

static char	**ft_tab(char const *s, char c, char **tab, int i)
{
	int	j;
	int	k;

	k = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while (s[i + j] && s[i + j] != c)
				j++;
			tab[k] = ft_substr(s, i, j);
			if (tab[k] == NULL)
			{
				free_tab(tab, k - 1);
				return (NULL);
			}
			k++;
			i += j;
		}
	}
	tab[k] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		len;
	char	**tab;

	if (!s)
		return (NULL);
	len = ft_count(s, c);
	tab = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tab)
	{
		return (NULL);
	}
	tab = ft_tab(s, c, tab, 0);
	if (!tab)
		return (NULL);
	return (tab);
}
