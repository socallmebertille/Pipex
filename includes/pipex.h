/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:24:33 by saberton          #+#    #+#             */
/*   Updated: 2024/09/18 18:26:15 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void	exec(char **path, char **envp, char *av);
void	parent_process(char **av, int *fd, char **envp);
void	child_process(char **av, int *fd, char **envp);
void	ft_free(char **path, char **cmd, char *tmp);
void	free_and_exit(char **path, char **cmd, char *tmp);
void	error_exit(int *fds, char *av, char **path);
int		open_file(char *av, int id);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*valid_cmd(char **path, char *cmd, char *tmp);
char	**ft_split(char const *s, char c);
char	**recup_path(char **envp);

#endif