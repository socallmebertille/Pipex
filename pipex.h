/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:26:01 by saberton          #+#    #+#             */
/*   Updated: 2024/07/13 18:57:21 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	close_fds(int *fds);
void	script_error(char **av, int i, int check);
int		execute_error(char **cmd);
int		execute_cmd(char **path, char **cmd, char **envp);
void	free_elem(char **path, char **cmd1, char **cmd2);
void	get_pipex(int ac, char **av, int i, char **envp);
int		check_av(char **av, int i);
int		child_process(char **av, int *fds, int pid, int i);
int		parent_process(char **av, int *fds, int pid, int ac);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c, char **tab);
char	**find_path(char **envp, int i);
char	**split_cmd2(char **av, int i, char **cmd);
char	**split_cmd(char **av, int i);

#endif