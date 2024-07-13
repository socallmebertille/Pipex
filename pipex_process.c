/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:51:12 by saberton          #+#    #+#             */
/*   Updated: 2024/07/13 18:58:18 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(int *fds)
{
	close(fds[0]);
	close(fds[1]);
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
		close_fds(fds);
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
		close_fds(fds);
		exit (0);
	}
	if (access(av[ac - 1], W_OK) == -1)
		exit(126);
	if (pid != 0)
	{
		dup2(fd2, STDOUT_FILENO);
		close(fd2);
		dup2(fds[0], STDIN_FILENO);
		close_fds(fds);
		return (1);
	}
	ft_putstr_fd("0\n", fd2);
	close(fd2);
	return (0);
}
