/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:46:42 by saberton          #+#    #+#             */
/*   Updated: 2024/07/13 18:55:23 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_path(char **envp, int i)
{
	int		j;
	int		len;
	char	*find;
	char	**path;

	path = NULL;
	find = "PATH=";
	while (envp[i])
	{
		j = 0;
		if (envp[i][j] == find[j])
		{
			while (envp[i][j] == find[j] && find[j])
				j++;
			len = ft_strlen(envp[i] + j);
			len -= ft_strlen(ft_strchr(envp[i] + j, ':'));
			if (len <= 0 && !find[j])
				path = ft_split(envp[i] + j, '.', path);
			else if (len > 0 && !find[j])
				path = ft_split(envp[i] + j, ':', path);
		}
		i++;
	}
	return (path);
}

int	execute_cmd(char **path, char **cmd, char **envp)
{
	char	*correct_path;
	char	*_path;
	int		env;
	int		i;

	env = -1;
	i = 0;
	while (env == -1 && path[i])
	{
		_path = ft_strjoin(path[i], "/");
		correct_path = ft_strjoin(_path, cmd[0]);
		env = execve(correct_path, cmd, envp);
		free(_path);
		free(correct_path);
		i++;
	}
	env = execve(cmd[0], cmd, envp);
	if (env == -1)
		return (execute_error(cmd));
	return (1);
}

int	check_av(char **av, int i)
{
	int	len;

	len = ft_strlen(av[i]);
	if (len > 2 && av[i][len - 3] == '.' && av[i][len - 2] == 's'
		&& av[i][len - 1] == 'h')
	{
		if (av[i][0] != '.' && av[i][1] != '/')
			return (-3);
		if (ft_strchr(av[i], ' ') != NULL)
			return (-2);
		if (access(av[i], W_OK) == -1)
			return (0);
		if (access(av[i], X_OK) == -1)
			return (-1);
		return (2);
	}
	return (1);
}

char	**split_cmd2(char **av, int i, char **cmd)
{
	cmd[1] = ft_strchr(av[i], ' ');
	cmd[0] = ft_substr(av[i], 0, ft_strlen(av[i]) - ft_strlen(cmd[1]));
	if (!cmd[0])
		return (NULL);
	cmd[2] = NULL;
	if (ft_strchr(cmd[1], 34) == NULL && ft_strchr(cmd[1], 39) == NULL)
	{
		free(cmd[0]);
		free(cmd);
		cmd = ft_split(av[i], ' ', NULL);
		if (!cmd)
			return (NULL);
		return (cmd);
	}
	while (*cmd[1] == ' ')
		cmd[1]++;
	if ((cmd[1][0] == 34 || cmd[1][0] == 39) && cmd[1])
	{
		cmd[1] = ft_substr(cmd[1], 1, ft_strlen(cmd[1]) - 2);
		if (!cmd[1])
			return (NULL);
	}
	return (cmd);
}

char	**split_cmd(char **av, int i)
{
	char	**cmd;

	if (check_av(av, i) == 0)
		return (NULL);
	if (ft_strchr(av[i], ' ') == NULL)
	{
		cmd = (char **)malloc(sizeof(char *) * 2);
		if (!cmd)
			return (NULL);
		cmd[0] = ft_strdup(av[i]);
		cmd[1] = NULL;
		return (cmd);
	}
	cmd = (char **)malloc(sizeof(char *) * 3);
	if (!cmd)
		return (NULL);
	cmd = split_cmd2(av, i, cmd);
	if (!cmd)
		return (NULL);
	return (cmd);
}
