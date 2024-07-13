/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertille <bertille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:54:57 by saberton          #+#    #+#             */
/*   Updated: 2024/07/13 15:50:02 by bertille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	while (count >= 0 && tab[count])
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

static int	ft_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c, char **tab)
{
	int		len;

	if (tab != NULL)
		free_tab(tab, ft_len(tab));
	if (!s)
		return (NULL);
	while (*s == ' ')
		s++;
	len = ft_count(s, c);
	tab = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	tab = ft_tab(s, c, tab, 0);
	if (!tab)
		return (NULL);
	return (tab);
}
