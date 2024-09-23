/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:08:03 by saberton          #+#    #+#             */
/*   Updated: 2024/09/21 18:24:17 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**recup_path(char **envp)
{
	char	*path;
	char	**path_file;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			path = ft_strdup(envp[i] + 5);
			if (!path)
				return (NULL);
			break ;
		}
		i++;
	}
	if (ft_strlen(path) == 0 || path == NULL)
		path_file = ft_split(".", ':');
	else
	{
		path_file = ft_split(path, ':');
		free(path);
	}
	return (path_file);
}

char	*valid_cmd(char **path, char *cmd, char *tmp)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (!cmd || !tmp || !*path || !path)
		return (NULL);
	while (path[i] && path)
	{
		cmd_path = ft_strjoin(path[i], tmp);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_strdup(""));
}
