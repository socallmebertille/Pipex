/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:37:35 by saberton          #+#    #+#             */
/*   Updated: 2024/09/21 15:45:10 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_free(char **path, char **cmd, char *tmp)
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
	if (cmd)
	{
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
	}
	if (tmp)
		free(tmp);
}

void	free_and_exit(char **path, char **cmd, char *tmp)
{
	if (*cmd)
		perror(*cmd);
	ft_free(path, cmd, tmp);
	exit(EXIT_FAILURE);
}

void	error_exit(int *fds, char *av, char **path)
{
	close(fds[0]);
	close(fds[1]);
	ft_free(path, NULL, NULL);
	perror(av);
	exit(EXIT_FAILURE);
}
