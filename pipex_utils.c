/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:40:22 by saberton          #+#    #+#             */
/*   Updated: 2024/07/10 23:54:10 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_path(char **envp)
{
	int		i;
	int		j;
	int		len;
	char	*find;
	char	**path;

	i = 0;
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
				path = ft_split(envp[i] + j, '.');
			else if (len > 0 && !find[j])
				path = ft_split(envp[i] + j, ':');
		}
		i++;
	}
	return (path);
}

int	check_av(char **av, int i)
{
	int	j;
	int	len;

	len = ft_strlen(av[i]);
	if (av[i][len - 3] == '.' && av[i][len - 2] == 's' && av[i][len - 1] == 'h')
	{
		if (av[i][0] != '.' && av[i][1] != '/')
			return (3);
		if (ft_strchr(av[i], ' ') != NULL)
		{
			ft_putstr_fd("/bin/sh: 1: ", 2);
			j = 0;
			while (av[i][j] != ' ')
				ft_putchar_fd(av[i][j++], 2);
			ft_putstr_fd(": not found\n", 2);
			return (0);
		}
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
		cmd = (char **)malloc(sizeof(char *) * 1);
		cmd[0] = ft_substr(av[i], 0, ft_strlen(av[i]));
		return (cmd);
	}
	cmd = (char **)malloc(sizeof(char *) * 2);
	if (cmd == NULL)
		return (NULL);
	cmd[1] = ft_strchr(av[i], ' ');
	cmd[0] = ft_substr(av[i], 0, ft_strlen(av[i]) - ft_strlen(cmd[1]));
	while (cmd[1][0] == ' ')
		cmd[1] = ft_substr(cmd[1], 1, ft_strlen(cmd[1]) - 1);
	if (cmd[1][0] == 34)
		cmd[1] = ft_substr(cmd[1], 1, ft_strlen(cmd[1]) - 2);
	else if (cmd[1][0] == 39)
		cmd[1] = ft_substr(cmd[1], 1, ft_strlen(cmd[1]) - 2);
	return (cmd);
}

// int    get_pipex(int ac, char **av, int i, int *fds, int pid)
// {
// 	char	**cmd1;
// 	char	**cmd2;

// 	cmd1 = split_cmd(av, i);
// 	cmd2 = split_cmd(av, i + 1);
// 	if (check_av(av, i + 1) == 3)
// 		return (3);
// 	if (child_process(av, fds, pid, i) == 1)
// 		return (1);
// 	if (parent_process(av, fds, pid, ac) == 1 && (i + 1) == (ac - 2))
// 		return (2);
// 	return (0);
// }