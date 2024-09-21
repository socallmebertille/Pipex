/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:14:35 by saberton          #+#    #+#             */
/*   Updated: 2024/09/21 15:18:02 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	exec(char **path, char **envp, char *av)
{
	char	*cmd_path;
	char	*tmp;
	char	**cmd;

	cmd = ft_split(av, ' ');
	if (!cmd || !*cmd)
		return (free_and_exit(path, NULL, NULL));
	tmp = ft_strjoin("/", cmd[0]);
	if (!tmp)
		return (free_and_exit(path, cmd, tmp));
	cmd_path = valid_cmd(path, *cmd, tmp);
	if (!cmd_path)
		return (free_and_exit(path, cmd, tmp));
	if (execve(cmd_path, cmd, envp) == -1)
		return (free(cmd_path), free_and_exit(path, cmd, tmp));
	return (free(cmd_path), ft_free(path, cmd, tmp));
}

int	open_file(char *av, int id)
{
	int	fd;

	if (id == 0)
		fd = open(av, O_RDONLY);
	if (id == 1)
		fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	return (fd);
}

void	parent_bonus(char **av, char **envp, int ac)
{
	char	**path;

	path = NULL;
	path = recup_path(envp);
	if (!path)
		exit(127);
	exec(path, envp, av[ac - 2]);
}

void	child_bonus(char **av, char **envp, int i)
{
	int		fd[2];
	char	**path;
	pid_t	pid;

	path = NULL;
	path = recup_path(envp);
	if (!path)
		exit(127);
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		exec(path, envp, av[i]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	infile;
	int	outfile;

	if (ac < 5)
		exit(EXIT_FAILURE);
	infile = open_file(av[1], 0);
	outfile = open_file(av[ac - 1], 1);
	dup2(infile, STDIN_FILENO);
	close(infile);
	i = 2;
	while (i < ac - 2)
		child_bonus(av, envp, i++);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	parent_bonus(av, envp, ac);
	return (0);
}
