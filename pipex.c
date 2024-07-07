/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:25:47 by saberton          #+#    #+#             */
/*   Updated: 2024/07/07 18:27:26 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**find_path(char **envp)
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
			if (!find[j])
			{
				len = ft_strlen(envp[i] + j);
				len -= ft_strlen(ft_strchr(envp[i] + j, ':'));
				path = ft_split(envp[i] + j, ':');
			}
		}
		i++;
	}
	return (path);
}

static void	execute_cmd(char **path, char **cmd, char **envp)
{
	char	*correct_path;
	int		env;
	int		i;

	env = -1;
	i = 0;
	while (env == -1 && path[i])
	{
		correct_path = ft_strjoin(path[i], "/");
		correct_path = ft_strjoin(correct_path, cmd[0]);
		env = execve(correct_path, cmd, envp);
		free(correct_path);
		i++;
	}
}

static char	**split_cmd(char **av, int i)
{
	char	**cmd;

	cmd = ft_split(av[i], ' ');
	if (cmd == NULL)
		return (NULL);
	return (cmd);
}

static int	child_process(char **av, int *fds, int pid, int i)
{
	int	fd1;

	fd1 = open(av[i - 1], O_RDONLY);
	if (fd1 == -1 && (i - 1) == 1)
	{
		close(fd1);
		ft_putstr_fd("zsh: no such file or directory: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	if (pid == 0)
	{
		dup2(fd1, STDIN_FILENO);
		close(fd1);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		close(fds[0]);
		return (1);
	}
	return (0);
}

static int	parent_process(char **av, int *fds, int pid, int ac)
{
	int	fd2;

	fd2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0640);
	if (pid != 0)
	{
		dup2(fd2, STDOUT_FILENO);
		close(fd2);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
		return (1);
	}
	ft_putstr_fd("0\n", fd2);
	close(fd2);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	**cmd1;
	char	**cmd2;
	char	**path;
	int		i;
	int		pid;
	int		fds[2];

	if (ac < 5)
		return (0);
	path = find_path(envp);
	pipe(fds);
	pid = fork();
	i = 2;
	while (i < ac - 1)
	{
		cmd1 = split_cmd(av, i);
		cmd2 = split_cmd(av, i + 1);
		if (child_process(av, fds, pid, i) == 1)
			execute_cmd(path, cmd1, envp);
		else if (child_process(av, fds, pid, i) == -1)
			return (parent_process(av, fds, 0, ac));
		if (parent_process(av, fds, pid, ac) == 1 && (i + 1) == (ac - 2))
			execute_cmd(path, cmd2, envp);
		else if ((i + 1) != ac - 2)
		{
			pipe(fds);
			pid = fork();
		}
		i++;
	}
	free(cmd1);
	free(cmd2);
	return (1);
}
