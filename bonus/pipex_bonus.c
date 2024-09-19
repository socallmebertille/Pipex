/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:14:35 by saberton          #+#    #+#             */
/*   Updated: 2024/09/19 16:52:51 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// void	exec(char **path, char **envp, char *av)
// {
// 	char	*cmd_path;
// 	char	*tmp;
// 	char	**cmd;
// 	int		i;

// 	cmd = ft_split(av, ' ');
// 	i = 0;
// 	while (cmd[i++])
// 		printf("cmd%d [%s]", i, cmd[i]);
// 	tmp = ft_strjoin("/", cmd[0]);
// 	if (!tmp || !cmd)
// 		return (free_and_exit(path, cmd, tmp));
// 	cmd_path = valid_cmd(path, *cmd, tmp);
// 	if (execve(cmd_path, cmd, envp) == -1)
// 		return (free_and_exit(path, cmd, tmp));
// 	return (ft_free(path, cmd, tmp));
// }

int	open_file(char *av, int id)
{
	int	fd;

	if (id == 0)
		fd = open(av, O_RDONLY);
	if (id == 1)
		fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

// void	parent_bonus(char **av, int *fd, char **envp, int ac)
// {
// 	int		outfile;
// 	char	**path;

// 	path = NULL;
// 	path = recup_path(envp);
// 	if (!path)
// 		exit(127);
// 	outfile = open_file(av[ac], 1);
// 	if (outfile == -1)
// 		error_exit(fd, av[ac], path);
// 	dup2(outfile, STDOUT_FILENO);
// 	dup2(fd[0], STDIN_FILENO);
// 	close(outfile);
// 	close(fd[0]);
// 	close(fd[1]);
// 	exec(path, envp, av[ac - 1]);
// }

// void	child_bonus(char **av, int *fd, char **envp, int i)
// {
// 	int		infile;
// 	char	**path;

// 	path = NULL;
// 	path = recup_path(envp);
// 	if (!path)
// 		exit(127);
// 	infile = open_file(av[1], 0);
// 	if (infile == -1)
// 		error_exit(fd, av[1], path);
// 	dup2(infile, STDIN_FILENO);
// 	dup2(fd[1], STDOUT_FILENO);
// 	close(infile);
// 	close(fd[0]);
// 	close(fd[1]);
// 	exec(path, envp, av[i]);
// }

// int	main(int ac, char **av, char **envp)
// {
// 	int		i;
// 	int		fd[2];
// 	int		prev_fd;
// 	pid_t	pid;

// 	if (ac < 5 || pipe(fd) == -1)
// 		exit(EXIT_FAILURE);
// 	prev_fd = -1;
// 	i = 2;
// 	while (i < ac - 2)
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (pid == 0)
// 		{
// 			if (prev_fd != -1)
// 			{
// 				dup2(prev_fd, STDIN_FILENO);
// 				close(prev_fd);
// 			}
// 			dup2(fd[1], STDOUT_FILENO);
// 			close(fd[0]);
// 			close(fd[1]);
// 			child_bonus(av, fd, envp, i);
// 		}
// 		else
// 		{
// 			close(fd[1]);
// 			if (prev_fd != -1)
// 				close(prev_fd);
// 			prev_fd = fd[0];
// 		}
// 		i++;
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (pid == 0)
// 	{
// 		if (prev_fd != -1)
// 		{
// 			dup2(prev_fd, STDIN_FILENO);
// 			close(prev_fd);
// 		}
// 		parent_bonus(av, fd, envp, ac);
// 	}
// 	else
// 	{
// 		close(prev_fd);
// 		waitpid(pid, NULL, 0);
// 	}
// 	return (0);
// }

void	exec_command(char **av, t_pipe *pipe_info, char **envp, int cmd_idx)
{
	char	**path;

	path = recup_path(envp);
	if (!path)
		exit(127);
	if (pipe_info->infile != -1)
		dup2(pipe_info->infile, STDIN_FILENO);
	if (pipe_info->outfile != -1)
		dup2(pipe_info->outfile, STDOUT_FILENO);
	if (pipe_info->infile != -1)
		close(pipe_info->infile);
	if (pipe_info->outfile != -1)
		close(pipe_info->outfile);
	if (execve(av[cmd_idx], &av[cmd_idx], envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	child_bonus(char **av, t_pipe *pipe_info, char **envp, int cmd_idx)
{
	close(pipe_info->fd[0]);
	exec_command(av, pipe_info, envp, cmd_idx);
}

void	parent_bonus(char **av, t_pipe *pipe_info, char **envp, int ac)
{
	close(pipe_info->fd[1]);
	pipe_info->outfile = open_file(av[ac - 1], 1);
	if (pipe_info->outfile == -1)
		error_exit(pipe_info->fd, av[ac - 1], NULL);
	exec_command(av, pipe_info, envp, ac - 2);
}

void	run_pipeline(char **av, char **envp, int ac, int infile)
{
	int		i;
	t_pipe	pipe_info;
	pid_t	pid;

	pipe_info.infile = infile;
	i = 2;
	while (i < ac - 2)
	{
		if (pipe(pipe_info.fd) == -1 || (pid = fork()) == -1)
		{
			perror("pipe/fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			child_bonus(av, &pipe_info, envp, i);
		close(pipe_info.fd[1]);
		close(pipe_info.infile);
		pipe_info.infile = pipe_info.fd[0];
		i++;
	}
	pid = fork();
	if (pid == 0)
		parent_bonus(av, &pipe_info, envp, ac);
	else
		close(pipe_info.infile);
}

int	main(int ac, char **av, char **envp)
{
	int	infile;

	if (ac < 5)
	{
		fprintf(stderr, "Usage: %s <infile> <cmd1> <cmd2> ... <outfile>\n",
			av[0]);
		exit(EXIT_FAILURE);
	}
	infile = open_file(av[1], 0);
	if (infile == -1)
	{
		perror(av[1]);
		exit(EXIT_FAILURE);
	}
	run_pipeline(av, envp, ac, infile);
	while (wait(NULL) > 0)
		;
	return (0);
}
