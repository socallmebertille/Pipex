/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:35:23 by saberton          #+#    #+#             */
/*   Updated: 2024/07/12 14:37:30 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	execute_cmd(char **path, char **cmd, char **envp);
void	script_error(char **av, int i, int check);
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
char	**ft_split(char const *s, char c);
char	**find_path(char **envp);
char	**split_cmd(char **av, int i);

#endif