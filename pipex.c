/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:25:47 by saberton          #+#    #+#             */
/*   Updated: 2024/07/13 07:10:43 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_cmd(char **path, char **cmd, char **envp)
{
	char	*correct_path;
	int		env;
	int		i;

	env = -1;
	i = 0;
	correct_path = "\0";
	while (env == -1 && path[i])
	{
		correct_path = ft_strcat(path[i], "/");
		correct_path = ft_strcat(correct_path, cmd[0]);
		// printf("%s\n", correct_path);
		env = execve(correct_path, cmd, envp);
		i++;
	}
	env = execve(cmd[0], cmd, envp);
	if (env == -1)
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		if (check_av(cmd, 0) == -1)
			exit(126);
		exit(127);
	}
	return (1);
}

int	child_process(char **av, int *fds, int pid, int i)
{
	int	fd1;

	fd1 = open(av[i - 1], O_RDONLY);
	if (fd1 == -1)
	{
		close(fd1);
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
	if (pid == -3)
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
		close(fds[1]);
		close(fds[0]);
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
	int		j;
	int		fds[2];

	if (ac < 5)
		exit(127);
	i = 2;
	if (check_av(av, i + 1) == -3)
	{
		script_error(av, i + 1, -3);
		return (parent_process(av, fds, -3, ac));
	}
	if (i < ac - 2)
	{
		get_pipex(ac, av, i, envp);
		j = i + 1;
		while (j < ac - 2)
		{
			get_pipex(ac, av, j, envp);
			printf("%s %d\n", av[j], j);
			j++;
		}
		i += j;
		// i++;
		// printf("%d\n", i);
	}
	return (1);
}

// int	main(int ac, char **av, char **envp)
// {
// 	int		fildes[2];
// 	int		pid;
// 	char	**cmd1;
// 	char	**cmd2;
// 	char	**path;

// 	path = find_path(envp, 0);
// 	cmd1 = split_cmd(av, 2);
// 	cmd2 = split_cmd(av, 3);
// 	// if (!cmd1 || !cmd2 || !path)
// 	// 	free_elem(path, cmd1, cmd2);
// 	if (ac == 5)
// 	{
// 		if (pipe(fildes) == -1)
// 			exit (EXIT_FAILURE);
// 		pid = fork();
// 		if (child_process(av, fildes, pid, 2) == 1)
// 			execute_cmd(path, cmd1, envp);
// 		if (pid == -1)
// 			exit (EXIT_FAILURE);
// 		if (parent_process(av, fildes, pid, ac) == 1)
// 			execute_cmd(path, cmd2, envp);
// 		free_elem(path, cmd1, cmd2);
// 		close(fildes[0]);
// 		close(fildes[1]);
// 		return (0);
// 	}
// 	exit(EXIT_FAILURE);
// }