/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:57:58 by saberton          #+#    #+#             */
/*   Updated: 2024/07/13 18:58:11 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_elem(char **path, char **cmd1, char **cmd2)
{
	int	i;

	i = 0;
	if (path)
	{
		while (path[i])
			free(path[i++]);
		free(path);
	}
	i = 0;
	if (cmd1)
	{
		while (cmd1[i])
			free(cmd1[i++]);
		free(cmd1);
	}
	i = 0;
	if (cmd2)
	{
		while (cmd2[i])
			free(cmd2[i++]);
		free(cmd2);
	}
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

int	execute_error(char **cmd)
{
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("\n", 2);
	if (check_av(cmd, 0) == -1)
		return (0);
	return (-1);
}
