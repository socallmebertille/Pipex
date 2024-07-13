/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:25:47 by saberton          #+#    #+#             */
/*   Updated: 2024/07/13 18:52:05 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
