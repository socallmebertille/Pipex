/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertille <bertille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:30:56 by saberton          #+#    #+#             */
/*   Updated: 2024/07/13 16:33:47 by bertille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *) s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (len + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (*s1 && i < len)
		join[i++] = *s1++;
	while (*s2 && i < len)
		join[i++] = *s2++;
	join[i] = '\0';
	return (join);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	i = 0;
	while (s[i])
		i++;
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	lens;

	i = 0;
	if (!s)
		return (NULL);
	lens = ft_strlen(s);
	if (start >= lens)
		return (ft_strdup(""));
	if (len > lens - start)
		len = lens - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (s[start] != '\0' && i < len && len != 0)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
