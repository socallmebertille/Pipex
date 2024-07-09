/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:25:47 by saberton          #+#    #+#             */
/*   Updated: 2024/07/09 23:00:03 by saberton         ###   ########.fr       */
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
	env = execve(cmd[0], cmd, envp);
	if (env == -1)
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
}

static int	check_av(char **av, int i)
{
	int	j;
	int	len;

	len = ft_strlen(av[i]);
	if (av[i][0] == '.' && av[i][1] == '/' && av[i][len - 3] == '.'
		&& av[i][len - 2] == 's' && av[i][len - 1] == 'h')
	{
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
		if (access(av[i], W_OK) == -1)
			return (1);
	}
	return (1);
}

static char	**split_cmd(char **av, int i)
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
	// printf("cmd [%s] flag [%s]\n", cmd[0], cmd[1]);
	return (cmd);
}

static int	child_process(char **av, int *fds, int pid, int i)
{
	int	fd1;

	fd1 = open(av[i - 1], O_RDONLY);
	if (fd1 == -1)
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

	fd2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 == -1)
		exit(2);
	if (access(av[ac - 1], W_OK) == -1)
		exit(126);
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
		exit(127);
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
		if (!cmd2 && access(av[i + 1], X_OK) == -1)
			exit(126);
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
