/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertille <bertille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:25:47 by saberton          #+#    #+#             */
/*   Updated: 2024/07/13 16:52:40 by bertille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_cmd(char **path, char **cmd, char **envp)
{
	char	*correct_path;
	char	*_path;
	int		env;
	int		i;

	env = -1;
	i = 0;
	// correct_path = NULL;
	while (env == -1 && path[i])
	{
		_path = ft_strjoin(path[i], "/");
		correct_path = ft_strjoin(_path, cmd[0]);
		// printf("%s\n", correct_path);
		env = execve(correct_path, cmd, envp);
		free(_path);
		free(correct_path);
		i++;
	}
	env = execve(cmd[0], cmd, envp);
	if (env == -1)
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		if (check_av(cmd, 0) == -1)
			return (0); //exit(126);
		return (-1); //exit(127);
	}
	return (1);
}

int	child_process(char **av, int *fds, int pid, int i)
{
	int	fd1;

	fd1 = open(av[i - 1], O_RDONLY);
	if (fd1 == -1)
	{
		ft_putstr_fd("zsh: no such file or directory: ", 2);
		ft_putstr_fd(av[i - 1], 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	if (pid == 0)
	{
		dup2(fd1, STDIN_FILENO);
		close(fd1);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		return (1);
	}
	return (0);
}

int	parent_process(char **av, int *fds, int pid, int ac)
{
	int	fd2;

	fd2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 == -1)
		exit(2);
	if (pid == -3 || access(av[ac - 1], W_OK) == -1)
	{
		close(fd2);
		close(fds[1]);
		close(fds[0]);
		exit (0);
	}
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

void	script_error(char **av, int i, int check)
{
	int	j;

	if (check > -2)
		return ;
	j = ft_strlen(ft_strchr(av[i], ' '));
	if (j != 0)
	{
		ft_putstr_fd("/bin/sh: 1: ", 2);
		ft_putstr_fd(ft_substr(av[i], 0, j), 2);
		ft_putstr_fd(": not found\n", 2);
	}
	else
	{
		ft_putstr_fd("/bin/sh: 1: ", 2);
		ft_putstr_fd(av[i], 2);
		ft_putstr_fd(": not found\n", 2);
	}
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	int		fds[2];

	if (ac < 5)
		exit(127);
	if (check_av(av, 3) == -3)
	{
		script_error(av, 3, -3);
		return (parent_process(av, fds, -3, ac));
	}
	i = 2;
	while (i < ac - 1)
	{
		get_pipex(ac, av, i, envp);
		printf("%d\n", i);
		i++;
	}
	return (1);
}
