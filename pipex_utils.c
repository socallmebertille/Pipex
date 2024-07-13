/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertille <bertille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:40:22 by saberton          #+#    #+#             */
/*   Updated: 2024/07/13 16:34:14 by bertille         ###   ########.fr       */
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
			// if (!path)
			// 	return (NULL);
		}
		i++;
	}
	return (path);
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
		// int j;
		// for (j = 0; cmd[j]; j++)
		// 	printf("cmd%d [%s][%d]\n", i - 2, cmd[j], j);
		// printf("cmd%d [%s][%d]\n", i - 2, cmd[j], j);
		return (cmd);
	}
	cmd = (char **)malloc(sizeof(char *) * 3);
	if (!cmd)
		return (NULL);
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
	// int j;
	// for (j = 0; cmd[j]; j++)
	// 	printf("cmd%d [%s][%d]\n", i - 2, cmd[j], j);
	// printf("cmd%d [%s][%d]\n", i - 2, cmd[j], j);
	return (cmd);
}

void	free_elem(char **path, char **cmd1, char **cmd2)
{
	int	i;

	i = 0;
	if (path)
	{
		while (path[i])
			free(path[i++]);
		free(path);
	}
	i = 0;
	if (cmd1)
	{
		while (cmd1[i])
			free(cmd1[i++]);
		free(cmd1);
	}
	i = 0;
	if (cmd2)
	{
		while (cmd2[i])
			free(cmd2[i++]);
		free(cmd2);
	}
}

void	get_pipex(int ac, char **av, int i, char **envp)
{
	char	**cmd1;
	char	**cmd2;
	char	**path;
	int		pid;
	int		exe;
	int		fds[2];

	if (pipe(fds))
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	path = find_path(envp, 0);
	cmd1 = split_cmd(av, i);
	cmd2 = split_cmd(av, i + 1);
	if (!path || !cmd1 || !cmd2)
		return (free_elem(path, cmd1, cmd2), exit(EXIT_FAILURE));
	exe = 1;
	if (check_av(av, i) == -2)
	{
		script_error(av, i, -2);
		if (child_process(av, fds, pid, i) == -1)
			exe = execute_cmd(path, cmd2, envp);
	}
	else if (child_process(av, fds, pid, i) == 1)
		exe = execute_cmd(path, cmd1, envp);
	if (exe == 0)
	{
		free_elem(path, cmd1, cmd2);
		exit (126);
	}
	if (exe == -1)
	{
		free_elem(path, cmd1, cmd2);
		exit (127);
	}
	if (parent_process(av, fds, pid, ac) == 1 && (i + 1) == (ac - 2))
		exe = execute_cmd(path, cmd2, envp);
	if (exe == 0)
	{
		free_elem(path, cmd1, cmd2);
		exit (126);
	}
	if (exe == -1)
	{
		free_elem(path, cmd1, cmd2);
		exit (127);
	}
	free_elem(path, cmd1, cmd2);
}
