/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:14:35 by saberton          #+#    #+#             */
/*   Updated: 2024/09/21 18:25:37 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec(char **path, char **envp, char *av)
{
	char	*cmd_path;
	char	*tmp;
	char	**cmd;

	cmd = ft_split(av, ' ');
	tmp = ft_strjoin("/", cmd[0]);
	if (!tmp || !cmd)
		return (free_and_exit(path, cmd, tmp));
	cmd_path = valid_cmd(path, *cmd, tmp);
	if (!cmd_path)
		return (free_and_exit(path, cmd, tmp));
	if (cmd_path[0] == '\0')
	{
		free(cmd_path);
		cmd_path = ft_strdup(*cmd);
	}
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
	return (fd);
}

void	parent_process(char **av, int *fd, char **envp)
{
	int		outfile;
	char	**path;

	path = NULL;
	path = recup_path(envp);
	if (!path)
		exit(127);
	outfile = open_file(av[4], 1);
	if (outfile == -1)
		error_exit(fd, av[4], path);
	dup2(outfile, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(outfile);
	close(fd[1]);
	exec(path, envp, av[3]);
}

void	child_process(char **av, int *fd, char **envp)
{
	int		infile;
	char	**path;

	path = NULL;
	path = recup_path(envp);
	if (!path)
		exit(127);
	infile = open_file(av[1], 0);
	if (infile == -1)
		error_exit(fd, av[1], path);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(infile);
	close(fd[0]);
	exec(path, envp, av[2]);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		pid1 = fork();
		if (pid1 == -1)
			exit(EXIT_FAILURE);
		if (pid1 == 0)
			child_process(av, fd, envp);
		pid2 = fork();
		if (pid2 == -1)
			exit(EXIT_FAILURE);
		if (pid2 == 0)
			parent_process(av, fd, envp);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
		return (0);
	}
	exit(EXIT_FAILURE);
}
